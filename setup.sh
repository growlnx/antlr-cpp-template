#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"

ANTLR_VERSION=4.9
JAR="lib/antlr-$ANTLR_VERSION-complete.jar"
URL="https://www.antlr.org/download/antlr-$ANTLR_VERSION-complete.jar"
JAR_SHA256=bd11b2464bc8aee5f51b119dff617101b77fa729540ee7f08241a6a672e6bc81
RUNTIME_INC=/usr/include/antlr4-runtime

fail=0
need() { command -v "$1" >/dev/null || { echo "missing: $1 ($2)"; fail=1; }; }

need java "JRE to run the ANTLR jar"
need clang++ "C++17 compiler"
need make "make"

if [ ! -f "$RUNTIME_INC/antlr4-runtime.h" ]; then
  echo "missing: ANTLR C++ runtime at $RUNTIME_INC (e.g. apt install libantlr4-runtime-dev)"
  fail=1
fi

if [ ! -f "$JAR" ]; then
  mkdir -p lib
  echo "downloading $URL"
  if command -v curl >/dev/null; then curl -fL "$URL" -o "$JAR"
  elif command -v wget >/dev/null; then wget -O "$JAR" "$URL"
  else echo "missing: curl or wget (or download the jar manually into lib/)"; fail=1
  fi
fi

if [ -f "$JAR" ] && ! echo "$JAR_SHA256  $JAR" | sha256sum -c --quiet -; then
  echo "sha256 mismatch: $JAR (delete it to download again)"
  fail=1
fi

[ "$fail" -eq 0 ] || exit 1
make antlr
echo "done: make (debug) or make release"
