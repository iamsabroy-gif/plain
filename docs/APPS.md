# Making apps: web sites and desktop windows

Two parts of the built-in library are for making programs other people use:

| | |
|---|---|
| `use "web"` | A web site or a web API: pages, forms, JSON, sessions, files. |
| `use "desktop"` | A program with a window: buttons, text boxes, lists, timers. |

Both are written in Plain (read them with `plain lib web` and `plain lib desktop`), and both
run with nothing to install. The examples are `examples/web_notes.plain` and
`examples/desktop_todo.plain`.

## Web sites: `use "web"`

```plain-example
use "web"
set app to new WebApp()

define home with request
    give back page("Hello", "<h1>Hello, world!</h1>")
end
define hello with request
    give back "Hello, {request's params's name}!"
end

app's get("/", home)
app's get("/hello/:name", hello)
app's start(8080)
```

Run it, then open `http://localhost:8080/` in a browser. `start` serves this computer only;
`start_and_open(8080)` also opens the browser, and `start_public(8080)` serves every
computer that can reach this one.

**Routes.** `app's get`, `post`, `put` and `delete` take a pattern and an action. A part
written `:name` matches anything and lands in `request's params's name`; a `*` at the end
matches the rest of the address (`request's params's rest`). A request for an address with
no route gets a "Not found" page; one with a route for another method gets "Not allowed".

**The request** is a map:

| Entry | Holds |
|---|---|
| `method`, `path` | `"GET"`, `"/hello/Asha"` |
| `params` | The `:name` parts of the route |
| `query` | What comes after `?` in the address, as a map |
| `form` | A sent HTML form, as a map |
| `json` | Sent JSON, already read (or `nothing`) |
| `headers`, `cookies`, `body` | The rest of the request (header names are lower case) |
| `session` | A map kept for this visitor between requests (see below) |

**What a handler gives back:**

| Give back | The visitor gets |
|---|---|
| Text | HTML if it starts with `<`, plain text otherwise |
| `page(title, html)` | A whole web page, with a tidy built-in style (light and dark) |
| A list or a map | JSON, for web APIs |
| `redirect("/somewhere")` | The browser goes there (after a form is sent, say) |
| `reply(404, "Not here")` | Any status, with text, HTML, or a list or map |
| `json_reply(value)` | JSON, even for a map with a `status` or `body` key |

`with_header(answer, name, value)` and `with_cookie(answer, name, value)` add to any answer.

**Safe HTML.** Text that visitors typed must never become part of a page as HTML, or one
visitor could change the page for others. `escape_html(text)` turns `< > & " '` into
codes: `"<li>" + escape_html(note) + "</li>"`. For HTML kept in its own file,
`fill(read_file("note.html"), {title: t, text: x})` fills in every `{{title}}` safely
(`{{!name}}` puts a value in as it is, for HTML you made yourself). Double braces, so
that Plain's own `"{name}"` templates leave them alone.

**Sessions.** `request's session` is a map that belongs to one visitor (a cookie remembers
which). Put anything in it, and it is there on their next request:

```plain-example
define visit with request
    set s to request's session
    if not has_key(s, "visits") then
        set s's visits to 0
    end
    increase s's visits by 1
    give back "You have been here {s's visits} times."
end
```

Sessions are kept in memory, so they end when the program stops.

**Files.** `app's folder("/files", "public")` sends the files in the folder `public`:
`public/cat.png` at `/files/cat.png`, and `public/index.html` for `/files/`. Nothing
outside the folder can be reached.

**Problems.** A handler that fails gives the visitor an error page that says what went
wrong (and the terminal shows it too). For a public site, `app's hide_errors()` shows
visitors "Something went wrong" instead. `app's quietly()` stops the line printed for
each request.

**Testing without a network.** `app's try_request("GET", "/hello/Asha", "")` answers one
request and gives back `{status, body, headers}`, so handlers can be checked in a normal
program: `say app's try_request("POST", "/notes", "text=Hi")'s status`.

## Desktop windows: `use "desktop"`

```plain-example
use "desktop"
set win to new Window("Counter", 360, 240)
set clicks to 0
set shown to win's label("Clicked 0 times")

define clicked
    increase clicks by 1
    shown's set_text("Clicked {clicks} times")
end

win's button("Click me", clicked)
win's run()
```

`run()` opens the window and answers it until it is closed; then the program carries on
after `run()`. The window is drawn by the browser engine already on the computer: in a
window of its own when Chrome, Edge, Chromium or Brave is installed, otherwise in a browser
tab. Only this computer can reach it, and only the window Plain opened (it carries a secret
that other pages don't have).

**Widgets.** Each of these gives back the widget, to read or change it later:

| Make | It is |
|---|---|
| `heading(words)`, `label(words)` | Text |
| `button(words, action)` | A button; the action runs when it is clicked |
| `input(label)`, `password(label)`, `number_input(label)`, `text_box(label)` | Places to type (one line, hidden, a number, several lines) |
| `checkbox(label)` | A tick box: its `value` is `true` or `false` |
| `choice(label, options)` | A drop-down list: its `value` is the option chosen |
| `slider(label, low, high)` | A slider: its `value` is a number |
| `list(items)` | A list; `when_picked(action)` makes the items clickable |
| `image(file)` | A picture from a file |
| `separator()` | A line |
| `row()`, `column()` | A box that holds widgets side by side, or stacked |

A widget's `value` is what the person typed, ticked or chose: `name_box's value`. A list's
`picked` is the number of the item clicked last, and `picked_item()` is that item.

**Changing widgets:** `set_text`, `set_value`, `set_items`, `set_placeholder`, `hide`,
`unhide`, `disable`, `enable`. The window shows the change as soon as the action finishes.

**Actions** take no values, and run when something happens: `button(words, action)`,
`when_clicked(action)`, `when_changed(action)` (typing, ticking, choosing, sliding),
`when_entered(action)` (Enter in a one-line input), `when_picked(action)` (a list item).

**The window:** `every(seconds, action)` runs an action again and again, `show_message(words)`
shows a note in the corner, `set_title(words)` and `close()` (the program carries on after
`run()`).

A problem in an action is shown in the window and the terminal, and the window keeps
working, so one mistake doesn't lose what the person typed.

**Giving it to someone.** `plain build todo.plain -o todo` makes one file that runs the
app on a computer without Plain.

## How it works (and what to know)

* **Web:** `http_serve` answers one request at a time, which is plenty for learning, a club's
  site, or a tool on a small network. A site with many visitors at once belongs behind a
  bigger web server (or written in a language made for that).
* **Desktop:** the program is a tiny web server that only the window can reach. The window
  checks in every second or two; when it is closed it says goodbye, and if it disappears
  without one (a crash) the program notices within a few seconds. A minimised window checks
  in rarely (browsers slow it down), so the program then waits much longer before deciding
  it has gone.
* **Windows:** the Windows build of Plain has no networking yet, so web and desktop apps run
  on Mac and Linux (and in WSL on Windows). See the [roadmap](ROADMAP.md).
* **Built-in actions underneath**, for other uses: `tcp_listen(port, "localhost")` listens on
  this computer only; `http_serve(server, handler, {how_many: n, idle: seconds})` gives back
  how many requests it answered, and a reply with `done: true` stops it;
  `open_url(address, {app: true, width: w, height: h})` opens a browser or an app window
  (`PLAIN_NO_BROWSER=1` only prints the address); `secure_token(16)` makes random text for
  secrets and session ids.
