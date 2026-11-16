// Plain - "plain lesson": the beginner lesson path, with exercises that are checked.
//
// A lesson is a text file in lib/lessons (NN-name.lesson):
//
//   # 3. Loops                      <- number and title
//   Teaching text. Lines indented by four spaces are code.
//   === Count to five               <- an exercise and its title
//   What to do (shown to the learner and put in their file).
//   --- output                      <- what the program must say (required)
//   --- input                       <- what is typed in for 'ask' (optional)
//   --- uses                        <- words the program must use, like: for, say (optional)
//   --- avoid                       <- words it must not use (optional)
//   --- hint                        <- one or more hints, separated by blank lines
//   --- solution                    <- a working program; plain lesson --selftest checks it
//
// The learner's program is run with the input typed in, and what it says (not the
// questions 'ask' shows) must match the expected output.
#pragma once
#include <map>
#include <sstream>

struct LessonExercise {
    std::string title, task, output, input, solution;
    std::vector<std::string> uses, avoid, hints;
};
struct Lesson {
    std::string id;  // the file name, like "03-loops"
    int number = 0;
    std::string title, teach;
    std::vector<LessonExercise> exercises;
};

static std::string trimEnds(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n"), b = s.find_last_not_of(" \t\r\n");
    return a == std::string::npos ? "" : s.substr(a, b - a + 1);
}
static std::vector<std::string> wordList(const std::string& s) {
    std::vector<std::string> out;
    std::string cur;
    for (char c : s + ",") {
        if (c == ',' || c == ' ' || c == '\n' || c == '\t') {
            if (!cur.empty()) out.push_back(cur);
            cur.clear();
        } else {
            cur += c;
        }
    }
    return out;
}

// Lines of one paragraph joined with spaces; blank lines stay as paragraph breaks.
static std::string joinLines(const std::string& s) {
    std::string out;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '\n' && i + 1 < s.size() && s[i + 1] != '\n' && (out.empty() || out.back() != '\n')) out += ' ';
        else out += s[i];
    }
    return out;
}

static Lesson parseLesson(const std::string& id, const std::string& text) {
    Lesson L;
    L.id = id;
    std::istringstream in(text);
    std::string line, section = "teach";
    LessonExercise* ex = nullptr;
    std::string buf;
    auto flush = [&]() {
        std::string body = section == "solution" || section == "output" || section == "input" ? buf : trimEnds(buf);
        if (!ex) L.teach = trimEnds(buf);
        else if (section == "task") ex->task = joinLines(trimEnds(body));
        else if (section == "output") ex->output = body;
        else if (section == "input") ex->input = body;
        else if (section == "solution") ex->solution = body;
        else if (section == "uses") ex->uses = wordList(body);
        else if (section == "avoid") ex->avoid = wordList(body);
        else if (section == "hint") {
            std::string h;
            std::istringstream hs(body + "\n\n");
            std::string hl;
            while (std::getline(hs, hl)) {
                if (trimEnds(hl).empty()) { if (!trimEnds(h).empty()) ex->hints.push_back(trimEnds(h)); h.clear(); }
                else h += (h.empty() ? "" : " ") + trimEnds(hl);
            }
        }
        buf.clear();
    };
    bool first = true;
    while (std::getline(in, line)) {
        if (first && line.compare(0, 2, "# ") == 0) {
            first = false;
            L.number = atoi(line.c_str() + 2);
            size_t dot = line.find(". ");
            L.title = dot == std::string::npos ? line.substr(2) : line.substr(dot + 2);
            continue;
        }
        first = false;
        if (line.compare(0, 4, "=== ") == 0) {
            flush();
            L.exercises.emplace_back();
            ex = &L.exercises.back();
            ex->title = trimEnds(line.substr(4));
            section = "task";
            continue;
        }
        if (ex && line.compare(0, 4, "--- ") == 0) {
            flush();
            section = trimEnds(line.substr(4));
            continue;
        }
        buf += line + "\n";
    }
    flush();
    return L;
}

static std::vector<Lesson> allLessons() {
    std::vector<Lesson> out;
    for (const LibFile* f = LIB_FILES; f->name; ++f)
        if (strncmp(f->name, "lessons/", 8) == 0) out.push_back(parseLesson(f->name + 8, f->text));
    std::sort(out.begin(), out.end(), [](const Lesson& a, const Lesson& b) { return a.number < b.number; });
    return out;
}

// ---- progress: "lesson exercise" pairs that are done, in .plain-lessons
static std::map<std::string, int> readLessonProgress() {
    std::map<std::string, int> done;  // "3.2" -> hints seen + 1000 if solved
    std::string text;
    if (!readFile(".plain-lessons", text)) return done;
    std::istringstream in(text);
    std::string key;
    int v;
    while (in >> key >> v) done[key] = v;
    return done;
}
static void writeLessonProgress(const std::map<std::string, int>& done) {
    std::string out;
    for (const auto& e : done) out += e.first + " " + std::to_string(e.second) + "\n";
    FILE* f = fopen(".plain-lessons", "wb");
    if (!f) return;
    fwrite(out.data(), 1, out.size(), f);
    fclose(f);
}
static std::string exKey(const Lesson& L, size_t i) { return std::to_string(L.number) + "." + std::to_string(i + 1); }
static bool exSolved(const std::map<std::string, int>& done, const std::string& key) {
    auto it = done.find(key);
    return it != done.end() && it->second >= 1000;
}

// Lines without trailing spaces, and no blank lines at the very end.
static std::string normalizeOutput(const std::string& s) {
    std::string out, line;
    std::istringstream in(s);
    while (std::getline(in, line)) {
        while (!line.empty() && (line.back() == ' ' || line.back() == '\r' || line.back() == '\t')) line.pop_back();
        out += line + "\n";
    }
    while (out.size() >= 2 && out[out.size() - 1] == '\n' && out[out.size() - 2] == '\n') out.pop_back();
    if (out == "\n") out.clear();
    return out;
}

struct LessonRun {
    bool ran = false;  // false: a mistake stopped it (message in 'problem')
    std::string output, problem;
};
// Run a program with 'input' typed in; collect what it says.
static LessonRun runForLesson(const std::string& src, const std::string& file, const std::string& input) {
    LessonRun r;
    auto run = std::make_unique<WatchedRun>();
    setUp(run->prog);
    VM vm(run->prog);
    run->ob.capture = true;
    run->ob.quietPrompts = true;
    run->ob.maxInstr = 50000000;
    vm.obs = &run->ob;
    std::istringstream typed(input);
    std::streambuf* saved = std::cin.rdbuf(typed.rdbuf());
    try {
        Compiler compiler(run->prog, src, file);
        Value mainFn = compiler.compileMain();
        vm.run(mainFn);
        r.ran = true;
    } catch (const PlainError& e) {
        r.problem = (e.line ? "Line " + std::to_string(e.line) + ": " : "") + e.msg;
    }
    std::cin.rdbuf(saved);
    std::cin.clear();
    for (const std::string& c : run->ob.outputChunks) r.output += c;
    return r;
}

// The words (and symbols) a program uses, for 'uses' and 'avoid'.
static std::vector<std::string> programWords(const std::string& src) {
    std::vector<std::string> out;
    try {
        for (const Token& t : tokenize(src))
            if (t.k == Token::Poss) {
                out.push_back("'s");
            } else if (t.k == Token::Kw || t.k == Token::Word || t.k == Token::Sym || t.k == Token::Num) {
                std::string w = t.text;
                for (char& c : w) c = (char)tolower((unsigned char)c);
                out.push_back(w);
                if (t.k == Token::Sym && t.text == "[") out.push_back("[]");
            } else if (t.k == Token::Str && !t.holes.empty()) {
                out.push_back("{}");  // a text template, and the words inside its braces
                for (const auto& h : t.holes)
                    for (const std::string& w : programWords(t.text.substr(h.first + 1, h.second - h.first - 1))) out.push_back(w);
            }
    } catch (const PlainError&) {
    }
    return out;
}
static bool usesWord(const std::vector<std::string>& words, const std::string& w) {
    return std::find(words.begin(), words.end(), w) != words.end();
}
static std::string describeWord(const std::string& w) {
    if (w == "{}") return "a text template like \"Hello {name}\"";
    if (w == "[]") return "a list, like [1, 2, 3]";
    if (w == "each") return "'for each'";
    if (w == "give") return "'give back'";
    if (w == "define") return "'define' (make your own action)";
    return "'" + w + "'";
}

// Check a program against one exercise. Returns "" when it passes, or what to fix.
static std::string checkExercise(const LessonExercise& ex, const std::string& src, const std::string& file, std::string* got = nullptr) {
    std::vector<std::string> words = programWords(src);
    for (const std::string& w : ex.uses)
        if (!usesWord(words, w)) return "This exercise is about using " + describeWord(w) + ", and your program doesn't use it yet.";
    for (const std::string& w : ex.avoid)
        if (usesWord(words, w)) return "Try this one without " + describeWord(w) + ".";
    LessonRun r = runForLesson(src, file, ex.input);
    if (got) *got = r.output;
    if (!r.ran) return "It stopped with a problem. " + r.problem;
    std::string want = normalizeOutput(ex.output), have = normalizeOutput(r.output);
    if (want == have) return "";
    // Say where it first differs.
    std::istringstream a(want), b(have);
    std::string la, lb;
    int n = 0;
    for (;;) {
        bool ga = (bool)std::getline(a, la), gb = (bool)std::getline(b, lb);
        ++n;
        if (!ga && !gb) break;
        if (ga && gb && la == lb) continue;
        std::string msg = "Line " + std::to_string(n) + " of what it says is not right.\n";
        msg += "      expected  " + (ga ? quote(la) : std::string("(nothing more)")) + "\n";
        msg += "      it said   " + (gb ? quote(lb) : std::string("(nothing more)"));
        return msg;
    }
    return "What it says is not quite right.";
}

static void showTeaching(const Lesson& L) {
    printf("\nLesson %d: %s\n\n", L.number, L.title.c_str());
    std::istringstream in(L.teach);
    std::string line, para;
    auto flushPara = [&]() {
        if (!trimEnds(para).empty()) printf("%s\n", wrapText(trimEnds(para), 78, "  ").c_str());
        para.clear();
    };
    while (std::getline(in, line)) {
        if (line.compare(0, 4, "    ") == 0) { flushPara(); printf("      %s\n", line.substr(4).c_str()); continue; }
        if (trimEnds(line).empty()) { flushPara(); printf("\n"); continue; }
        para += line + " ";
    }
    flushPara();
}

static std::string exerciseFile(const Lesson& L, size_t i) { return "lesson" + std::to_string(L.number) + "-" + std::to_string(i + 1) + ".plain"; }
static std::string exerciseStarter(const Lesson& L, size_t i) {
    const LessonExercise& ex = L.exercises[i];
    std::string s = "# Lesson " + std::to_string(L.number) + ", exercise " + std::to_string(i + 1) + ": " + ex.title + "\n#\n";
    s += wrapText(ex.task, 76, "# ");
    if (!ex.input.empty()) s += "#\n# When it is checked, this is typed in: " + clip(trimEnds(ex.input), 50) + "\n";
    s += "#\n# Check it with:  plain lesson " + std::to_string(L.number) + "\n# Stuck?         plain lesson " + std::to_string(L.number) + " --hint\n\n";
    return s;
}
static void showExercise(const Lesson& L, size_t i) {
    const LessonExercise& ex = L.exercises[i];
    printf("\nExercise %zu of %zu: %s\n\n%s", i + 1, L.exercises.size(), ex.title.c_str(), wrapText(ex.task, 78, "  ").c_str());
    if (!ex.input.empty()) printf("\n  When it is checked, this is typed in:  %s\n", clip(trimEnds(ex.input), 50).c_str());
    printf("\n  It should say:\n");
    std::istringstream o(ex.output);
    std::string line;
    while (std::getline(o, line)) printf("    %s\n", line.c_str());
}

// Make the file for exercise i if it isn't there yet. Gives true if it was just made.
static bool ensureExerciseFile(const Lesson& L, size_t i) {
    std::string path = exerciseFile(L, i);
    if (fileExists(path)) return false;
    FILE* f = fopen(path.c_str(), "wb");
    if (!f) return false;
    std::string t = exerciseStarter(L, i);
    fwrite(t.data(), 1, t.size(), f);
    fclose(f);
    return true;
}

static int lessonSelftest(const std::vector<Lesson>& all) {
    int bad = 0, count = 0;
    for (const Lesson& L : all) {
        if (L.number <= 0 || L.title.empty() || L.teach.empty()) { printf("%s: needs '# N. Title' and teaching text\n", L.id.c_str()); ++bad; }
        for (size_t i = 0; i < L.exercises.size(); ++i) {
            const LessonExercise& ex = L.exercises[i];
            ++count;
            if (ex.output.empty() || ex.solution.empty() || ex.hints.empty() || ex.task.empty()) {
                printf("lesson %d exercise %zu: needs a task, output, hint and solution\n", L.number, i + 1);
                ++bad;
                continue;
            }
            std::string got, why = checkExercise(ex, ex.solution, "<solution>", &got);
            if (!why.empty()) { printf("lesson %d exercise %zu (%s): the solution fails: %s\n", L.number, i + 1, ex.title.c_str(), why.c_str()); ++bad; }
            // The starter alone must not pass.
            if (checkExercise(ex, exerciseStarter(L, i), "<starter>").empty()) { printf("lesson %d exercise %zu: the empty starter passes\n", L.number, i + 1); ++bad; }
        }
    }
    printf("%zu lessons, %d exercises: %s\n", all.size(), count, bad ? "PROBLEMS FOUND" : "every solution passes its checks");
    return bad ? 1 : 0;
}

// plain lesson [n] [--hint] [--solution] [--show] [--selftest]
static int lessonCommand(const std::vector<std::string>& args) {
    int number = 0;
    bool hint = false, solution = false, show = false, selftest = false;
    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "--hint") hint = true;
        else if (args[i] == "--solution") solution = true;
        else if (args[i] == "--show") show = true;
        else if (args[i] == "--selftest") selftest = true;
        else number = atoi(args[i].c_str());
    }
    std::vector<Lesson> all = allLessons();
    if (selftest) return lessonSelftest(all);
    std::map<std::string, int> done = readLessonProgress();
    if (number == 0) {
        printf("\nLessons. Start with:  plain lesson 1\n\n");
        for (const Lesson& L : all) {
            size_t solved = 0;
            for (size_t i = 0; i < L.exercises.size(); ++i) solved += exSolved(done, exKey(L, i));
            printf("  %2d  %-28s %zu of %zu exercises done%s\n", L.number, L.title.c_str(), solved, L.exercises.size(),
                   solved == L.exercises.size() && solved ? "  \xE2\x9C\x93" : "");
        }
        printf("\nAfter the lessons:  plain practice  (50 problems with hidden tests)\n\n");
        return 0;
    }
    const Lesson* found = nullptr;
    for (const Lesson& L : all)
        if (L.number == number) found = &L;
    if (!found) { fprintf(stderr, "There is no lesson %d. See them all with: plain lesson\n", number); return 2; }
    const Lesson& L = *found;
    // the exercise to work on: the first one not done yet
    size_t cur = 0;
    while (cur < L.exercises.size() && exSolved(done, exKey(L, cur))) ++cur;
    if (show) {
        showTeaching(L);
        if (cur < L.exercises.size()) showExercise(L, cur);
        return 0;
    }
    if (cur == L.exercises.size()) {
        showTeaching(L);
        printf("\nYou have done every exercise in this lesson. \xE2\x9C\x93\n");
        if (number < (int)all.size()) printf("Next:  plain lesson %d\n", number + 1);
        return 0;
    }
    const LessonExercise& ex = L.exercises[cur];
    std::string key = exKey(L, cur);
    if (hint) {
        int seen = done[key] % 1000;
        if (seen >= (int)ex.hints.size()) {
            printf("\nThat was the last hint. To see a working program:  plain lesson %d --solution\n", number);
            return 0;
        }
        printf("\nHint %d of %zu:\n%s\n", seen + 1, ex.hints.size(), wrapText(ex.hints[(size_t)seen], 78, "  ").c_str());
        done[key] = done[key] / 1000 * 1000 + seen + 1;
        writeLessonProgress(done);
        return 0;
    }
    if (solution) {
        if (done[key] % 1000 < (int)ex.hints.size()) {
            printf("\nTry the hints first:  plain lesson %d --hint\n", number);
            return 0;
        }
        printf("\nA program that works (yours may be different and just as good):\n\n%s\n", ex.solution.c_str());
        return 0;
    }
    std::string path = exerciseFile(L, cur);
    if (ensureExerciseFile(L, cur)) {
        if (cur == 0) showTeaching(L);
        showExercise(L, cur);
        printf("\nI made %s for you. Write your program in it, then check it with:  plain lesson %d\n", path.c_str(), number);
        return 0;
    }
    std::string src;
    if (!readFile(path, src)) { fprintf(stderr, "I couldn't open '%s'.\n", path.c_str()); return 2; }
    if (src == exerciseStarter(L, cur)) {
        showExercise(L, cur);
        printf("\n%s is still empty. Write your program in it, then run  plain lesson %d  again.\n", path.c_str(), number);
        return 1;
    }
    printf("\nChecking %s (exercise %zu: %s)\n", path.c_str(), cur + 1, ex.title.c_str());
    std::string why = checkExercise(ex, src, path);
    if (!why.empty()) {
        printf("\n  \xE2\x9C\x97 %s\n\nFix it and run  plain lesson %d  again. Stuck?  plain lesson %d --hint   Watch it:  plain visualize %s\n",
               why.c_str(), number, number, path.c_str());
        return 1;
    }
    printf("\n  \xE2\x9C\x93 Well done! That's right.\n");
    done[key] = 1000 + done[key] % 1000;
    writeLessonProgress(done);
    if (cur + 1 < L.exercises.size()) {
        ensureExerciseFile(L, cur + 1);
        showExercise(L, cur + 1);
        printf("\nI made %s for the next one. Check it with:  plain lesson %d\n", exerciseFile(L, cur + 1).c_str(), number);
    } else {
        printf("\nThat was the last exercise of lesson %d.%s\n", number,
               number < (int)all.size() ? (" Next:  plain lesson " + std::to_string(number + 1)).c_str() : " You have finished every lesson! Try  plain practice  next.");
    }
    return 0;
}
