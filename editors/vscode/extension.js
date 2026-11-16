// Plain for VS Code: run, visualize, format, and underline mistakes found by 'plain check'.
const vscode = require("vscode");
const { execFile } = require("child_process");
const path = require("path");

function plainCommand() {
    return vscode.workspace.getConfiguration("plain").get("path") || "plain";
}

// "Oops! Line 3: The 'if' ... never closed." -> { line: 3, message: "The 'if' ..." }
function parseProblem(output) {
    const m = /Line (\d+):\s*(.*)/.exec(output);
    if (!m) return null;
    return { line: Math.max(0, parseInt(m[1], 10) - 1), message: m[2].trim() };
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

    // plain check on save: underline the first mistake it finds.
    function check(doc) {
        if (doc.languageId !== "plain" || doc.uri.scheme !== "file") return;
        if (!vscode.workspace.getConfiguration("plain").get("checkOnSave")) return;
        execFile(plainCommand(), ["check", doc.fileName], { cwd: path.dirname(doc.fileName) }, (err, stdout, stderr) => {
            const problem = err ? parseProblem(stderr + stdout) : null;
            if (!problem) return diagnostics.set(doc.uri, []);
            const line = Math.min(problem.line, doc.lineCount - 1);
            const range = doc.lineAt(line).range;
            diagnostics.set(doc.uri, [new vscode.Diagnostic(range, problem.message, vscode.DiagnosticSeverity.Error)]);
        });
    }
    context.subscriptions.push(
        vscode.workspace.onDidSaveTextDocument(check),
        vscode.workspace.onDidOpenTextDocument(check),
        vscode.workspace.onDidCloseTextDocument((doc) => diagnostics.delete(doc.uri))
    );
    vscode.workspace.textDocuments.forEach(check);
}

function deactivate() {}

module.exports = { activate, deactivate, parseProblem };
