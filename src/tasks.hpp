// Plain - background tasks, channels, locks and the cycle collector.
#pragma once
#include <chrono>
#include <deque>

#include "vm.hpp"

namespace plain {

// ------------------------------------------------------- cycle collector
// Reference counting frees most things at once. Objects that only refer to each
// other (a list that contains itself, an object and its helper) are found here
// by "trial deletion": take away every reference that comes from another tracked
// object; whatever still has references is used by the program, and everything
// reachable from it stays. The rest is garbage.
inline bool isTracked(const Value& v) {
    if (v.tag != Value::Object) return false;
    switch (v.o->kind) {
        case Kind::List: case Kind::Map: case Kind::Closure: case Kind::Upval:
        case Kind::Class: case Kind::Instance: case Kind::Bound: case Kind::Handle: return true;
        default: return false;
    }
}
struct GcCounter : Visitor {
    void visit(const Value& v) override {
        if (isTracked(v)) --static_cast<GCObj*>(v.o)->gcRefs;
    }
};
struct GcMarker : Visitor {
    std::vector<GCObj*> work;
    void visit(const Value& v) override {
        if (!isTracked(v)) return;
        GCObj* o = static_cast<GCObj*>(v.o);
        if (!o->gmark) {
            o->gmark = true;
            work.push_back(o);
        }
    }
};
inline size_t collectGarbage() {
    for (GCObj* o = g_gc.head; o; o = o->gnext) {
        o->gcRefs = (int64_t)o->rc;
        o->gmark = false;
    }
    GcCounter counter;
    for (GCObj* o = g_gc.head; o; o = o->gnext) o->traverse(counter);
    GcMarker marker;
    for (GCObj* o = g_gc.head; o; o = o->gnext)
        if (o->gcRefs > 0 && !o->gmark) {
            o->gmark = true;
            marker.work.push_back(o);
        }
    while (!marker.work.empty()) {
        GCObj* o = marker.work.back();
        marker.work.pop_back();
        o->traverse(marker);
    }
    std::vector<GCObj*> garbage;
    for (GCObj* o = g_gc.head; o; o = o->gnext)
        if (!o->gmark) garbage.push_back(o);
    for (GCObj* o : garbage) ++o->rc;
    for (GCObj* o : garbage) o->clearRefs();
    for (GCObj* o : garbage)
        if (--o->rc == 0) delete o;
    g_gc.allocs = 0;
    g_gc.threshold = std::max<size_t>(100000, g_gc.live);
    return garbage.size();
}

// ------------------------------------------------------ waiting for events
// Every change that another task may be waiting for (a task finishing, a message
// arriving, a lock being let go) bumps this counter. A waiter remembers the value
// it saw, gives up its turn, and sleeps until the counter moves.
struct Events {
    std::mutex m;
    std::condition_variable cv;
    uint64_t version = 0;
};
inline Events& events() {
    static Events e;
    return e;
}
inline void signalEvent() {
    Events& e = events();
    {
        std::lock_guard<std::mutex> l(e.m);
        ++e.version;
    }
    e.cv.notify_all();
}
inline uint64_t eventVersion() {
    Events& e = events();
    std::lock_guard<std::mutex> l(e.m);
    return e.version;
}
// Wait (without holding the turn) until something changes, or the time is up.
inline void waitForEvent(uint64_t seen, double seconds = -1) {
    fflush(stdout);
    Unlocked u;
    Events& e = events();
    std::unique_lock<std::mutex> l(e.m);
    if (seconds < 0) e.cv.wait(l, [&] { return e.version != seen; });
    else e.cv.wait_for(l, std::chrono::duration<double>(seconds), [&] { return e.version != seen; });
}

// ----------------------------------------------------------------- handles
struct TaskHandle : Handle {
    bool done = false, failed = false;
    Value result;
    std::string error;
    std::string label() const override { return "task"; }
};
struct ChannelHandle : Handle {
    std::deque<Value> queue;
    bool closed = false;
    void traverse(Visitor& vis) override { for (const Value& v : queue) vis.visit(v); }
    void clearRefs() override { queue.clear(); }
    std::string label() const override { return "channel"; }
};
struct LockHandle : Handle {
    bool held = false;
    std::string label() const override { return "lock"; }
};

template <class T>
inline T* argHandle(const char* fn, Value* a, int i, const char* what) {
    T* h = isKind(a[i], Kind::Handle) ? dynamic_cast<T*>(static_cast<Handle*>(a[i].o)) : nullptr;
    if (!h) fail(std::string("'") + fn + "' needs " + what + ", but I got " + describe(a[i]) + ".");
    return h;
}

inline Value startTask(VM& vm, Value* a, int n) {
    if (n < 1) fail("'start_task' needs an action to run.");
    if (!(a[0].tag == Value::Object && (a[0].o->kind == Kind::Closure || a[0].o->kind == Kind::Native || a[0].o->kind == Kind::Bound)))
        fail(std::string("'start_task' needs an action to run, but I got ") + describe(a[0]) + ".");
    TaskHandle* task = new TaskHandle;
    Value tv = Value::obj(task);
    Value callee = a[0];
    std::vector<Value> values(a + 1, a + n);
    Program* prog = &vm.prog;
    tasksStarted() = true;
    std::thread([tv, callee, values, prog]() mutable {
        gil().lock();
        {
            TaskHandle* t = static_cast<TaskHandle*>(tv.o);
            Value result;
            std::string error;
            bool failed = false;
            try {
                VM worker(*prog, 1 << 18);
                result = worker.call(callee, values);
            } catch (const PlainError& e) {
                failed = true;
                error = e.msg;
            } catch (const std::exception& e) {
                failed = true;
                error = e.what();
            }
            t->result = std::move(result);
            t->error = error;
            t->failed = failed;
            t->done = true;
            callee.clear();
            values.clear();
            tv.clear();
        }
        fflush(stdout);
        signalEvent();
        gil().unlock();
    }).detach();
    return tv;
}

inline Value waitFor(VM&, Value* a, int) {
    TaskHandle* t = argHandle<TaskHandle>("wait_for", a, 0, "a task made by 'start_task'");
    Value keep = a[0];
    for (;;) {
        uint64_t seen = eventVersion();
        if (t->done) break;
        waitForEvent(seen);
    }
    if (t->failed) fail("The background task failed: " + t->error);
    return t->result;
}
inline Value taskDone(VM&, Value* a, int) {
    return Value::boolean(argHandle<TaskHandle>("task_done", a, 0, "a task made by 'start_task'")->done);
}

inline Value makeChannel(VM&, Value*, int) { return Value::obj(new ChannelHandle); }
inline Value channelSend(VM&, Value* a, int) {
    ChannelHandle* c = argHandle<ChannelHandle>("send", a, 0, "a channel made by 'channel'");
    if (c->closed) fail("I can't send to a channel that has been closed.");
    c->queue.push_back(a[1]);
    signalEvent();
    return Value();
}
// receive(channel) waits for the next message; it gives back nothing once the channel is closed and empty.
inline Value channelReceive(VM&, Value* a, int n) {
    if (n < 1 || n > 2) fail("'receive' needs a channel and, optionally, a number of seconds to wait.");
    ChannelHandle* c = argHandle<ChannelHandle>("receive", a, 0, "a channel made by 'channel'");
    double limit = -1;
    if (n == 2) {
        if (!isNumber(a[1])) fail(std::string("'receive' needs a number of seconds, but I got ") + describe(a[1]) + ".");
        limit = toDouble(a[1]);
    }
    Value keep = a[0];
    auto start = std::chrono::steady_clock::now();
    for (;;) {
        uint64_t seen = eventVersion();
        if (!c->queue.empty()) {
            Value v = std::move(c->queue.front());
            c->queue.pop_front();
            signalEvent();
            return v;
        }
        if (c->closed) return Value();
        double left = -1;
        if (limit >= 0) {
            left = limit - std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
            if (left <= 0) fail("I waited " + fmt(a[1]) + " seconds, but no message arrived.");
        }
        waitForEvent(seen, left);
    }
}
inline Value channelClose(VM&, Value* a, int) {
    argHandle<ChannelHandle>("close_channel", a, 0, "a channel made by 'channel'")->closed = true;
    signalEvent();
    return Value();
}
inline Value channelSize(VM&, Value* a, int) {
    return Value::integer((int64_t)argHandle<ChannelHandle>("messages_waiting", a, 0, "a channel made by 'channel'")->queue.size());
}

inline Value makeLock(VM&, Value*, int) { return Value::obj(new LockHandle); }
inline Value lockAcquire(VM&, Value* a, int) {
    LockHandle* l = argHandle<LockHandle>("acquire", a, 0, "a lock made by 'lock'");
    Value keep = a[0];
    for (;;) {
        uint64_t seen = eventVersion();
        if (!l->held) break;
        waitForEvent(seen);
    }
    l->held = true;
    return Value();
}
inline Value lockRelease(VM&, Value* a, int) {
    LockHandle* l = argHandle<LockHandle>("release", a, 0, "a lock made by 'lock'");
    if (!l->held) fail("I can't release a lock that isn't held.");
    l->held = false;
    signalEvent();
    return Value();
}
inline Value lockTry(VM&, Value* a, int) {
    LockHandle* l = argHandle<LockHandle>("try_acquire", a, 0, "a lock made by 'lock'");
    if (l->held) return Value::boolean(false);
    l->held = true;
    return Value::boolean(true);
}
inline Value gcCollect(VM&, Value*, int) { return Value::integer((int64_t)collectGarbage()); }

inline void registerTaskBuiltins(Program& prog) {
    struct Entry { const char* name; int arity; NativeFn fn; };
    static const Entry table[] = {
        {"start_task", -1, startTask}, {"wait_for", 1, waitFor}, {"task_done", 1, taskDone},
        {"channel", 0, makeChannel}, {"send", 2, channelSend}, {"receive", -1, channelReceive},
        {"close_channel", 1, channelClose}, {"messages_waiting", 1, channelSize},
        {"lock", 0, makeLock}, {"acquire", 1, lockAcquire}, {"release", 1, lockRelease}, {"try_acquire", 1, lockTry},
        {"collect_garbage", 0, gcCollect},
    };
    for (const Entry& e : table) prog.define(e.name, Value::obj(new Native(e.name, e.arity, e.fn)));
}

}  // namespace plain
