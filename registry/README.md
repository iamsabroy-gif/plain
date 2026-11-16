# The Plain package index

`index.json` is the shared list that `plain install NAME` and `plain search` read. It
maps a package name to where its code lives:

```json
{
  "greeter": {
    "spec": "someone/plain-greeter",
    "description": "Friendly greetings in many languages"
  }
}
```

`spec` is anything `plain install` accepts: `user/repo` (on GitHub), or a full git
address.

## Add your package

1. Put your package in a public git repository with a `plain.json`
   (`plain init` makes one) and tag its versions: `git tag v1.0.0 && git push --tags`.
2. Open a pull request that adds one entry to `index.json`. Names are lower case
   letters, digits, `-` and `_`, and are first come, first served.

## Versions

People can then ask for a range of versions, and get the newest tagged one that fits:

| Ask for | Gets |
|---|---|
| `plain install greeter` | the newest code on the default branch |
| `plain install greeter#^1.2` | the newest 1.x that is at least 1.2 |
| `plain install greeter#~1.2.3` | the newest 1.2.x that is at least 1.2.3 |
| `plain install greeter#1.x` | the newest 1.x |
| `plain install "greeter#>=1.0 <3.0"` | the newest version from 1.0 up to (not including) 3.0 |
| `plain install greeter#v1.4.0` | exactly that tag |

`plain.lock` remembers the exact commit, so installing again gives the same code;
`plain update greeter` looks for a newer version that still fits.

## Your own index

Set `PLAIN_REGISTRY` to a file or web address with the same format (or create
`~/.plain/registry.json`). It is read first, so it can add private packages or
override shared ones.
