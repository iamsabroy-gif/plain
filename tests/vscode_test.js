// The VS Code extension's checking (editors/vscode/extension.js), run against the real build/plain with a
// small stand-in for VS Code's API: type a program, wait, and see which line is underlined.
//   node tests/vscode_test.js
const Module = require("module");
const path = require("path");
const ROOT = path.join(__dirname, ".."), PLAIN = path.join(ROOT, "build", "plain");
const handlers = {}, shown = new Map();
const settings = { path: PLAIN, checkAsYouType: true, checkOnSave: true };
const stub = {
  workspace: {
    getConfiguration: () => ({ get: (k) => settings[k] }),
    onDidChangeTextDocument: (f) => { handlers.change = f; return {}; },
    onDidSaveTextDocument: (f) => { handlers.save = f; return {}; },
    onDidOpenTextDocument: (f) => { handlers.open = f; return {}; },
    onDidCloseTextDocument: (f) => { handlers.close = f; return {}; },
    textDocuments: [],
  },
  languages: {
    createDiagnosticCollection: () => ({ set: (uri, d) => shown.set(String(uri), d), delete: (uri) => shown.delete(String(uri)), dispose() {} }),
    registerDocumentFormattingEditProvider: () => ({}),
  },
  commands: { registerCommand: () => ({}) },
  window: { terminals: [], createTerminal: () => ({}), showWarningMessage() {} },
  Diagnostic: class { constructor(range, message, severity) { this.range = range; this.message = message; this.severity = severity; } },
  DiagnosticSeverity: { Error: 0, Warning: 1 },
  TextEdit: { replace: (r, t) => ({ r, t }) },
  Range: class { constructor(a, b) { this.a = a; this.b = b; } },
};
const load = Module._load;
Module._load = function (request, ...rest) { return request === "vscode" ? stub : load.call(this, request, ...rest); };
const ext = require(path.join(ROOT, "editors", "vscode", "extension.js"));
ext.activate({ subscriptions: [] });

const results = [];
const ok = (c, what) => results.push((c ? "ok   " : "FAIL ") + what);
const sleep = (ms) => new Promise((r) => setTimeout(r, ms));
function doc(text) {
  const lines = text.split("\n");
  return { languageId: "plain", uri: { scheme: "file", toString: () => "file:///t.plain" }, isClosed: false, lineCount: lines.length, getText: () => text,
           lineAt: (n) => ({ range: "line " + (n + 1), text: lines[n] }) };
}
async function typed(text) {
  shown.delete("file:///t.plain");
  handlers.change({ document: doc(text) });
  await sleep(1400);   // the extension waits half a second after typing stops, then asks plain
  return shown.get("file:///t.plain");
}
(async () => {
  let d = await typed('set total to 0\ntotal = 5\nsay total\n');
  ok(d && d.length === 1 && d[0].range === "line 2" && d[0].severity === 0 && /start the line with 'set'/.test(d[0].message), "a mistake is an error on its own line");
  d = await typed('set x to 1\nif x is 1 then\n    say x\n');
  ok(d && d.length === 1 && d[0].range === "line 2" && d[0].severity === 1, "a block that is not closed yet is only a warning, on the line that opens it");
  d = await typed('say "all fine"\n');
  ok(d && d.length === 0, "a good program has nothing underlined");
  settings.checkAsYouType = false;
  shown.delete("file:///t.plain");
  handlers.change({ document: doc("x = 1\n") });
  await sleep(1200);
  ok(!shown.has("file:///t.plain"), "typing is ignored when plain.checkAsYouType is off");
  handlers.save(doc("x = 1\n"));
  await sleep(900);
  ok(shown.get("file:///t.plain") && shown.get("file:///t.plain").length === 1, "but saving still checks");
  settings.path = "/nonexistent/plain";
  handlers.save(doc("x = 1\n"));
  await sleep(500);
  ok(shown.get("file:///t.plain").length === 0, "with no plain command it says nothing instead of failing");
  const failed = results.filter((r) => r.startsWith("FAIL"));
  if (failed.length) { console.log(results.join("\n")); process.exit(1); }
  console.log("vscode: ok (" + results.length + " checks)");
  process.exit(0);
})();
