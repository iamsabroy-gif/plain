// Plain for VS Code: run, visualize, format, and underline mistakes (found by 'plain check') as you type.
const vscode = require("vscode");
const { execFile } = require("child_process");
const path = require("path");

function plainCommand() {
    return vscode.workspace.getConfiguration("plain").get("path") || "plain";
}

// What "plain check --json -" said (one line of JSON) as a problem to underline, or null.
//   {"ok":false,"line":3,"message":"...","incomplete":false}
function parseCheck(output) {
  let v;
  try { v = JSON.parse(String(output).trim().split("\n")[0]); } catch (e) { return null; }
  if (!v || v.ok !== false || (v.file && v.file !== "program.plain")) return null;
  return { line: Math.max(0, (v.line || 1) - 1), message: v.message || "There is a mistake here.", incomplete: !!v.incomplete };
}

function runInTerminal(args, cwd) {
    let term = vscode.window.terminals.find((t) => t.name === "Plain");
    if (!term) term = vscode.window.createTerminal({ name: "Plain", cwd });
    term.show(true);
    const quote = (s) => (/[\s"'$`\\]/.test(s) ? JSON.stringify(s) : s);
    term.sendText([plainCommand(), ...args].map(quote).join(" "));
}

async function currentPlainFile() {
    const editor = vscode.window.activeTextEditor;
    if (!editor || editor.document.languageId !== "plain") {
        vscode.window.showWarningMessage("Open a .plain file first.");
        return null;
    }
    if (editor.document.isDirty) await editor.document.save();
    return editor.document;
}

function activate(context) {
    const diagnostics = vscode.languages.createDiagnosticCollection("plain");
    context.subscriptions.push(diagnostics);

    context.subscriptions.push(
        vscode.commands.registerCommand("plain.run", async () => {
            const doc = await currentPlainFile();
            if (doc) runInTerminal([doc.fileName], path.dirname(doc.fileName));
        }),
        vscode.commands.registerCommand("plain.visualize", async () => {
            const doc = await currentPlainFile();
            if (doc) runInTerminal(["visualize", doc.fileName], path.dirname(doc.fileName));
        })
    );

    // Format Document: plain format --print (it never changes what a program does).
    context.subscriptions.push(
        vscode.languages.registerDocumentFormattingEditProvider("plain", {
            provideDocumentFormattingEdits(doc) {
                return new Promise((resolve) => {
                    const child = execFile(plainCommand(), ["format", "--print", "-"], { maxBuffer: 1 << 26 }, (err, stdout) => {
                        if (err || !stdout) return resolve([]);
                        const all = new vscode.Range(doc.positionAt(0), doc.positionAt(doc.getText().length));
                        resolve([vscode.TextEdit.replace(all, stdout)]);
                    });
                    child.stdin.end(doc.getText());
                });
            },
        })
    );

    // Mistakes, underlined as you type (a moment after you stop) and when a file is opened or saved.
    // The text is sent to "plain check --json -", so nothing needs saving first. A block that is
    // still open is only a warning (you are probably still typing it).
    const config = () => vscode.workspace.getConfiguration("plain");
    const timers = new Map();
    function check(doc) {
        if (doc.languageId !== "plain" || doc.uri.scheme === "output") return;
        const child = execFile(plainCommand(), ["check", "--json", "-"], { maxBuffer: 1 << 24 }, (err, stdout) => {
            const problem = parseCheck(stdout);
            if (!problem || doc.isClosed) return diagnostics.set(doc.uri, []);
            const line = Math.min(problem.line, doc.lineCount - 1);
            const d = new vscode.Diagnostic(doc.lineAt(line).range, problem.message,
                problem.incomplete ? vscode.DiagnosticSeverity.Warning : vscode.DiagnosticSeverity.Error);
            d.source = "plain";
            diagnostics.set(doc.uri, [d]);
        });
        child.on("error", () => diagnostics.set(doc.uri, []));   // no plain command: say nothing
        child.stdin.on("error", () => {});
        child.stdin.end(doc.getText());
    }
    function checkSoon(doc) {
        clearTimeout(timers.get(doc.uri.toString()));
        timers.set(doc.uri.toString(), setTimeout(() => check(doc), 500));
    }
    context.subscriptions.push(
        vscode.workspace.onDidChangeTextDocument((e) => { if (config().get("checkAsYouType")) checkSoon(e.document); }),
        vscode.workspace.onDidSaveTextDocument((doc) => { if (config().get("checkOnSave")) check(doc); }),
        vscode.workspace.onDidOpenTextDocument((doc) => { if (config().get("checkOnSave") || config().get("checkAsYouType")) check(doc); }),
        vscode.workspace.onDidCloseTextDocument((doc) => { clearTimeout(timers.get(doc.uri.toString())); diagnostics.delete(doc.uri); })
    );
    vscode.workspace.textDocuments.forEach((doc) => { if (config().get("checkOnSave") || config().get("checkAsYouType")) check(doc); });
}

function deactivate() {}

module.exports = { activate, deactivate, parseCheck };
