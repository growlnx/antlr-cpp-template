# Minimal ANTLR4 C++ Template

Minimal ANTLR 4.9 + C++17 project using the visitor pattern. It reads a file
from `argv`, parses it and walks the parse tree with a visitor.

## Dependencies

- `clang++` (C++17), `make`
- Java (JRE), only to run the ANTLR tool jar
- ANTLR C++ runtime **4.9** (must match the jar version)
- `clang-format` **19.1.7** (optional; the build skips formatting if missing)
- `curl` or `wget` (only if the jar is not in `lib/` yet)

On Debian:

```bash
sudo apt install clang clang-format make default-jre libantlr4-runtime-dev curl
```

## Setup

Checks the tools, downloads the pinned `antlr-4.9-complete.jar` into `lib/`
(SHA-256 verified) and generates the lexer/parser.

```bash
./setup.sh
```

## Building

```bash
make            # debug   -> build/debug/<TARGET>
make release    # release -> build/release/<TARGET>
make antlr      # only regenerate the ANTLR sources
make format     # clang-format our sources (also runs before every build)
make clean      # remove build/ and the generated sources
```

The binary name is `TARGET` at the top of `src/Makefile`.

`make` can be run from any directory: `make -C path/to/project`.

## Formatting

Style lives in `.clang-format`, fully explicit and generated with
clang-format 19.1.7. Other versions may format differently or reject some
options, so use the same version (e.g. `pipx install clang-format==19.1.7`, or
the binary bundled with the VS Code C/C++ extension). Generated `Grammar*`
files are never formatted by `make format`.

## Running

```bash
build/debug/<TARGET> <file>
```

## Layout

```
src/Grammar.g4   grammar (edit this)
src/main.cpp     CLI, lexer/parser setup
src/ast.h/.cpp   AST nodes and printing (no ANTLR dependency)
src/builder.*    visitor: parse tree -> AST
src/Makefile     build rules (list new .cpp files in SRCS)
lib/             ANTLR jar (downloaded, not versioned)
build/           binaries
.clang-format    formatting style (pinned to clang-format 19.1.7)
```

Generated files (`src/Grammar*.cpp|h|interp|tokens`) are not versioned. Run
`make antlr` after changing the grammar or cloning the repo.
