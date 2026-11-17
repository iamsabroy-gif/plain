# Advanced features

None of this is needed for the first seven lessons (see [CORE.md](CORE.md)). It is all
still part of Plain.

## Anonymous actions and closures

```plain
set double to action with x gives x * 2
say map_each([1, 2, 3], double)            # [2, 4, 6]

define make_counter
    set count to 0
    define bump
        increase count by 1
        give back count
    end
    give back bump
end
set next to make_counter()
say next(), next()                         # 1 2
```

An action can be stored, passed and returned. It keeps the variables of the
action it was made in (one counter per `make_counter()` call). Every round of a
`for` / `for each` loop gets its own copy of the loop's variable (and, inside an
action, of the variables made in the loop's body), so closures made in different
rounds keep different values. (Variables made with `set` in a loop body at the top
level are shared by the whole program; put the loop in an action to get one per round.) `map_each`, `keep_if`, `find_first`,
`combine(items, start, action)` and `sort_by(items, action)` take actions.
A longer anonymous action can use a block: `action with a, b` … `give back …` … `end`.

## Classes and methods

```plain
class Animal
    init with name
        set me's name to name
    end
    define speak
        say me's name + " makes a sound"
    end
end

class Dog extends Animal
    init with name
        parent's init(name)
    end
    define speak
        say me's name + " barks"
    end
end

set rex to new Dog("Rex")
rex's speak()
say is_a(rex, Animal)            # true
```

`init` runs when an object is made. `me` is the object, `parent's name(...)`
calls the parent class's action. An object can define `to_text` (no values) to
say how it is shown by `say`. Fields are created by `set me's field to …`.

## Tasks, channels and locks

```plain-example
set results to channel()
define work with id
    send(results, id * 10)
end
set t to start_task(work, 4)
say receive(results)               # 40
wait_for(t)
```

`start_task(action, values…)` runs an action alongside the program;
`wait_for(task)` gives its answer (or its error). `channel()`, `send`, `receive`
(waits; `nothing` once the channel is closed and empty), `close_channel`, and
`lock()` with `acquire` / `release` / `try_acquire`. Tasks are real operating-system
threads that take turns running Plain code (a global interpreter lock, like Python),
so they overlap while waiting for files, the network or `wait`, but do not run
Plain code on several cores at once. Use a lock around a change that must not be
interleaved, such as `set counter to counter + 1`.

## Networking

| Action | What it does |
|---|---|
| `http_get(url [, headers])` | `{status, body, headers}`. `http://` and `https://` are built in (https uses the computer's OpenSSL, checks the site's certificate and follows `HTTPS_PROXY`; without OpenSSL it uses the `curl` program, and `PLAIN_HTTPS=curl` asks for that). |
| `http_post(url, body [, headers])`, `http_request(method, url, body, headers)` | A list or map body is sent as JSON. |
| `tcp_listen(port [, "localhost"])`, `tcp_port(server)`, `tcp_accept`, `tcp_connect(host, port)` | Plain TCP. A connection is a number. With `"localhost"`, only this computer can connect. |
| `tcp_send`, `tcp_receive`, `tcp_receive_line`, `tcp_close` | |
| `http_serve(server, handler [, how_many or {how_many, idle}])` | A small web server: `handler` gets `{method, path, query, headers, body}` and gives back text, a list/map (sent as JSON), or `{status, body, headers}` (`done: true` stops the server after that reply; a header given a list is sent once per item). `idle`: stop when no request came for that many seconds. Gives back how many requests it answered. For whole sites, see `use "web"` in [APPS.md](APPS.md). |
| `open_url(address [, {app, width, height}])` | Opens a browser, or with `app: true` a window of its own. `PLAIN_NO_BROWSER=1` only prints the address. |
| `secure_token([bytes])` | Random text from the operating system, for secrets and session ids. |
| `url_encode`, `url_decode` | |

## Packages

A project can list what it needs in `plain.json`:

```
{ "name": "shop", "version": "1.0.0", "main": "main.plain",
  "dependencies": { "greeter": "someone/plain-greeter#v1.2.0", "tools": "../tools" } }
```

| Command | Does |
|---|---|
| `plain init` | Writes `plain.json`. |
| `plain install` | Installs everything `plain.json` lists, into `./plain_modules`, and writes `plain.lock`. |
| `plain install name[#version]` | A package from the index, or `user/repo`, a git address, or a folder. Added to `plain.json`. `--as name` picks the name, `--global` installs for every project. |
| `plain search [words]` | Lists packages in the index whose name or description has the words. |
| `plain update [name]` | Fetches newer versions, ignoring `plain.lock`. |
| `plain remove name`, `plain list` | |

`plain.lock` pins each git package to the exact commit, so an install on another
computer gets the same code. In a program, `use "greeter"` loads the package's
`main` file (from its `plain.json`, or `main.plain`); `use "greeter/extra"` loads
another file of it. A package that needs other packages gets them installed too.
`plain install name` looks the name up in your own index (`PLAIN_REGISTRY` or
`~/.plain/registry.json`) if you have one, then in the shared index
([registry/](../registry/README.md)), which anyone can add a package to.

The version after `#` can be a tag (`#v1.4.0`) or a range, and Plain picks the newest
tagged version that fits: `#^1.2` (1.2 or newer, below 2), `#~1.2.3` (below 1.3),
`#1.x`, `#>=1.0 <3.0`, `#^1 || ^2`.
`plain build` bundles the program and its packages into one executable.

