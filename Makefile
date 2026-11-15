# Plain - build, test and install.
#   make            build ./build/plain
#   make test       run the test programs
#   make install    copy plain into $(PREFIX)/bin   (default /usr/local; may need sudo)
CXX ?= c++
CXXFLAGS ?= -O2 -std=c++17 -Wall -Wextra
PREFIX ?= /usr/local

all: build/plain

src/libfiles.hpp: $(wildcard lib/*.plain lib/problems/*.plain lib/viz/*.html)
	sh tools/embed.sh

build/plain: src/main.cpp src/*.hpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ src/main.cpp

test: build/plain
	@sh tests/run_tests.sh build/plain
	@sh tests/pkg_test.sh build/plain
	@sh tests/format_test.sh build/plain
	@sh tests/lib_test.sh build/plain
	@sh tests/viz_test.sh build/plain
	@sh tests/practice_test.sh build/plain
	@sh tests/webmode_test.sh
	@sh tests/docs_test.sh build/plain
	@if command -v node >/dev/null 2>&1; then node tests/wasm_test.js && node tests/web_e2e.js; fi

install: build/plain
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m 755 build/plain $(DESTDIR)$(PREFIX)/bin/plain

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/plain

clean:
	rm -rf build

.PHONY: all test install uninstall clean
