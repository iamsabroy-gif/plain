// Plain - https without curl. OpenSSL is loaded when it is first needed (not linked), so a
// ready-made plain still runs on computers without it: web requests then go through curl.
#pragma once
#ifdef PLAIN_POSIX
#include <dlfcn.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string>

namespace plain {

struct TlsLib {
    bool ok = false;
    void* ctx = nullptr;  // one shared client context: trusted certificates, verification on
    int (*init_ssl)(uint64_t, const void*) = nullptr;
    const void* (*client_method)() = nullptr;
    void* (*ctx_new)(const void*) = nullptr;
    int (*ctx_default_paths)(void*) = nullptr;
    void (*ctx_set_verify)(void*, int, void*) = nullptr;
    long (*ctx_ctrl)(void*, int, long, void*) = nullptr;
    void* (*ssl_new)(void*) = nullptr;
    int (*set_fd)(void*, int) = nullptr;
    long (*ssl_ctrl)(void*, int, long, void*) = nullptr;
    int (*set1_host)(void*, const char*) = nullptr;
    int (*connect)(void*) = nullptr;
    int (*read)(void*, void*, int) = nullptr;
    int (*write)(void*, const void*, int) = nullptr;
    int (*shutdown)(void*) = nullptr;
    void (*free)(void*) = nullptr;
    long (*verify_result)(const void*) = nullptr;
    unsigned long (*err_get)() = nullptr;
    void (*err_string)(unsigned long, char*, size_t) = nullptr;
    const char* (*verify_string)(long) = nullptr;

    static TlsLib& get() {
        static TlsLib lib = load();
        return lib;
    }

private:
    template <typename F>
    static bool sym(void* h, const char* name, F& out) {
        out = reinterpret_cast<F>(dlsym(h, name));
        return out != nullptr;
    }
    static TlsLib load() {
        TlsLib t;
        const char* force = getenv("PLAIN_HTTPS");
        if (force && std::string(force) == "curl") return t;  // asked to use curl
        static const char* names[] = {
            "libssl.so.3", "libssl.so.1.1", "libssl.so",
            "/opt/homebrew/opt/openssl@3/lib/libssl.3.dylib", "/usr/local/opt/openssl@3/lib/libssl.3.dylib",
            "libssl.3.dylib", "libssl.1.1.dylib",
        };
        void* h = nullptr;
        for (const char* n : names)
            if ((h = dlopen(n, RTLD_NOW | RTLD_LOCAL))) break;
        if (!h) return t;
        bool all = sym(h, "OPENSSL_init_ssl", t.init_ssl) && sym(h, "TLS_client_method", t.client_method) &&
                   sym(h, "SSL_CTX_new", t.ctx_new) && sym(h, "SSL_CTX_set_default_verify_paths", t.ctx_default_paths) &&
                   sym(h, "SSL_CTX_set_verify", t.ctx_set_verify) && sym(h, "SSL_CTX_ctrl", t.ctx_ctrl) &&
                   sym(h, "SSL_new", t.ssl_new) && sym(h, "SSL_set_fd", t.set_fd) && sym(h, "SSL_ctrl", t.ssl_ctrl) &&
                   sym(h, "SSL_set1_host", t.set1_host) && sym(h, "SSL_connect", t.connect) && sym(h, "SSL_read", t.read) &&
                   sym(h, "SSL_write", t.write) && sym(h, "SSL_shutdown", t.shutdown) && sym(h, "SSL_free", t.free) &&
                   sym(h, "SSL_get_verify_result", t.verify_result) && sym(h, "ERR_get_error", t.err_get) &&
                   sym(h, "ERR_error_string_n", t.err_string) && sym(h, "X509_verify_cert_error_string", t.verify_string);
        if (!all) return t;  // too old (before OpenSSL 1.1) or not OpenSSL at all
        t.init_ssl(0, nullptr);
        t.ctx = t.ctx_new(t.client_method());
        if (!t.ctx) return t;
        t.ctx_default_paths(t.ctx);         // the system's trusted certificates (and SSL_CERT_FILE)
        t.ctx_set_verify(t.ctx, 1, nullptr);  // SSL_VERIFY_PEER: refuse servers we can't verify
        t.ctx_ctrl(t.ctx, 123, 0x0303, nullptr);  // SSL_CTX_set_min_proto_version(TLS 1.2)
        t.ok = true;
        return t;
    }
};

inline bool nativeTlsAvailable() { return TlsLib::get().ok; }

// A network connection: a socket, plus a TLS session for https.
struct Conn {
    int fd = -1;
    void* ssl = nullptr;
    Conn(int f = -1) : fd(f) {}
};
inline long connSend(const Conn& c, const char* data, size_t n) {
    if (c.ssl) return TlsLib::get().write(c.ssl, data, (int)std::min(n, (size_t)1 << 30));
    return (long)send(c.fd, data, n, 0);
}
inline long connRecv(const Conn& c, char* buf, size_t n) {
    if (c.ssl) return TlsLib::get().read(c.ssl, buf, (int)std::min(n, (size_t)1 << 30));
    return (long)recv(c.fd, buf, n, 0);
}
inline void connClose(Conn& c) {
    if (c.ssl) {
        TlsLib::get().shutdown(c.ssl);
        TlsLib::get().free(c.ssl);
        c.ssl = nullptr;
    }
    if (c.fd >= 0) close(c.fd);
    c.fd = -1;
}

inline std::string tlsErrorText() {
    TlsLib& t = TlsLib::get();
    unsigned long e = t.err_get();
    if (!e) return "";
    char buf[256];
    t.err_string(e, buf, sizeof buf);
    return buf;
}

// Turn a connected socket into a verified TLS connection to 'host'. Gives "" or what went wrong.
inline std::string startTls(Conn& c, const std::string& host) {
    TlsLib& t = TlsLib::get();
    c.ssl = t.ssl_new(t.ctx);
    if (!c.ssl) return "couldn't start a secure connection";
    t.set_fd(c.ssl, c.fd);
    t.ssl_ctrl(c.ssl, 55, 0, const_cast<char*>(host.c_str()));  // SNI: say which site we want
    t.set1_host(c.ssl, host.c_str());                            // and check the certificate is for it
    if (t.connect(c.ssl) != 1) {
        long v = t.verify_result(c.ssl);
        std::string why = v != 0 ? std::string("its certificate can't be trusted (") + t.verify_string(v) + ")" : tlsErrorText();
        t.free(c.ssl);
        c.ssl = nullptr;
        return why.empty() ? "the secure connection failed" : why;
    }
    return "";
}

// ---- proxies (HTTPS_PROXY / https_proxy, and NO_PROXY), like curl uses
inline std::string base64(const std::string& in) {
    static const char* tbl = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string out;
    size_t i = 0;
    for (; i + 2 < in.size(); i += 3) {
        unsigned v = ((unsigned char)in[i] << 16) | ((unsigned char)in[i + 1] << 8) | (unsigned char)in[i + 2];
        out += tbl[v >> 18]; out += tbl[(v >> 12) & 63]; out += tbl[(v >> 6) & 63]; out += tbl[v & 63];
    }
    if (i + 1 == in.size()) {
        unsigned v = (unsigned char)in[i] << 16;
        out += tbl[v >> 18]; out += tbl[(v >> 12) & 63]; out += "==";
    } else if (i + 2 == in.size()) {
        unsigned v = ((unsigned char)in[i] << 16) | ((unsigned char)in[i + 1] << 8);
        out += tbl[v >> 18]; out += tbl[(v >> 12) & 63]; out += tbl[(v >> 6) & 63]; out += '=';
    }
    return out;
}
inline bool noProxyFor(const std::string& host) {
    const char* np = getenv("NO_PROXY");
    if (!np) np = getenv("no_proxy");
    if (!np) return false;
    std::string list = np, h = host;
    for (char& ch : h) ch = (char)tolower((unsigned char)ch);
    size_t start = 0;
    while (start <= list.size()) {
        size_t comma = list.find(',', start);
        std::string e = list.substr(start, comma == std::string::npos ? std::string::npos : comma - start);
        start = comma == std::string::npos ? list.size() + 1 : comma + 1;
        while (!e.empty() && e[0] == ' ') e.erase(0, 1);
        while (!e.empty() && e.back() == ' ') e.pop_back();
        for (char& ch : e) ch = (char)tolower((unsigned char)ch);
        if (e == "*") return true;
        if (e.compare(0, 2, "*.") == 0) e.erase(0, 1);
        if (e.empty()) continue;
        if (h == e || (e[0] == '.' && h.size() > e.size() && h.compare(h.size() - e.size(), e.size(), e) == 0) ||
            (e[0] != '.' && h.size() > e.size() && h.compare(h.size() - e.size() - 1, e.size() + 1, "." + e) == 0))
            return true;
    }
    return false;
}
struct Proxy {
    std::string host, port, auth;  // auth: "user:password", if the address has one
};
inline bool httpsProxyFor(const std::string& host, Proxy& p) {
    const char* v = getenv("HTTPS_PROXY");
    if (!v || !*v) v = getenv("https_proxy");
    if (!v || !*v || noProxyFor(host)) return false;
    std::string s = v;
    size_t scheme = s.find("://");
    if (scheme != std::string::npos) {
        if (s.compare(0, scheme, "http") != 0) return false;  // only http proxies (as curl does by default)
        s = s.substr(scheme + 3);
    }
    size_t slash = s.find('/');
    if (slash != std::string::npos) s.resize(slash);
    size_t at = s.rfind('@');
    if (at != std::string::npos) { p.auth = s.substr(0, at); s = s.substr(at + 1); }
    size_t colon = s.rfind(':');
    p.host = colon == std::string::npos ? s : s.substr(0, colon);
    p.port = colon == std::string::npos ? "80" : s.substr(colon + 1);
    return !p.host.empty();
}

inline int dialTcp(const std::string& host, const std::string& port, int timeoutSeconds) {
    struct addrinfo hints, *res = nullptr;
    memset(&hints, 0, sizeof hints);
    hints.ai_socktype = SOCK_STREAM;
    int fd = -1;
    if (getaddrinfo(host.c_str(), port.c_str(), &hints, &res) != 0) return -1;
    for (struct addrinfo* p = res; p; p = p->ai_next) {
        fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (fd < 0) continue;
        struct timeval tv;
        tv.tv_sec = timeoutSeconds;
        tv.tv_usec = 0;
        setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);
        setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof tv);
        if (connect(fd, p->ai_addr, p->ai_addrlen) == 0) break;
        close(fd);
        fd = -1;
    }
    freeaddrinfo(res);
    return fd;
}

// Open a connection to host:port, secure if 'tls' (through the https proxy if one is set).
// Gives "" or what went wrong. Touches no Plain values, so it can run while other tasks do.
inline std::string openConn(const std::string& host, const std::string& port, bool tls, Conn& c) {
    Proxy px;
    bool viaProxy = tls && httpsProxyFor(host, px);
    c.fd = viaProxy ? dialTcp(px.host, px.port, 30) : dialTcp(host, port, 30);
    if (c.fd < 0) return viaProxy ? "couldn't reach the proxy " + px.host + ":" + px.port : "couldn't connect to " + host + " on port " + port;
    if (viaProxy) {
        std::string req = "CONNECT " + host + ":" + port + " HTTP/1.1\r\nHost: " + host + ":" + port + "\r\n";
        if (!px.auth.empty()) req += "Proxy-Authorization: Basic " + base64(px.auth) + "\r\n";
        req += "\r\n";
        if (send(c.fd, req.data(), req.size(), 0) != (ssize_t)req.size()) { connClose(c); return "couldn't talk to the proxy"; }
        std::string head;
        char ch;
        while (head.size() < 16384 && head.find("\r\n\r\n") == std::string::npos && recv(c.fd, &ch, 1, 0) == 1) head += ch;
        size_t sp = head.find(' ');
        int code = sp == std::string::npos ? 0 : atoi(head.c_str() + sp + 1);
        if (code != 200) { connClose(c); return "the proxy refused the connection (" + head.substr(0, head.find('\r')) + ")"; }
    }
    if (tls) {
        std::string why = startTls(c, host);
        if (!why.empty()) { connClose(c); return "couldn't make a secure connection to " + host + ": " + why; }
    }
    return "";
}

}  // namespace plain
#endif
