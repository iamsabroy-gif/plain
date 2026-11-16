# Homebrew

`plain.rb` is a Homebrew formula that builds Plain from source (it only needs the
compiler that comes with Xcode's command line tools).

## Publish it (once)

1. Create a public repository called `homebrew-plain` under the same account.
2. Copy `plain.rb` into it as `Formula/plain.rb` and push.

Then anyone can install the latest code with:

    brew install --HEAD iamsabroy-gif/plain/plain

## After each release

When a version is tagged (`git tag v2.2.0 && git push --tags`), fill in the download
address and its checksum, then copy the formula to the tap again:

    sh tools/update-formula.sh v2.2.0

After that, `brew install iamsabroy-gif/plain/plain` (without `--HEAD`) installs that
version, and `brew upgrade` picks up new ones.
