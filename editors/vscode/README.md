# Plain for VS Code

- **Colours** for `.plain` files, including the values inside text templates like `"Hello {name}"`.
- **Indenting**: a new line after `if`, `for`, `define` … is indented, and `end` / `otherwise` move back out.
- **Snippets**: type `if`, `foreach`, `for`, `define`, `class`, `try` and press Tab.
- **Run** (F5, or the ▶ button): runs the program in a terminal called Plain.
- **Plain: Watch this program run** opens `plain visualize` for the file.
- **Format Document** (Shift+Alt+F) uses `plain format`, which never changes what a program does.
- **Mistakes underlined on save** using `plain check`.

It needs the `plain` command (see the main README). If it is not on your PATH, set
`plain.path` in Settings to its full path.

## Install

Until it is on the Marketplace, build the package and install it:

    cd editors/vscode
    npx @vscode/vsce package
    code --install-extension plain-language-0.1.0.vsix

(or in VS Code: Extensions, the `…` menu, **Install from VSIX…**).
