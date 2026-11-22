TARGET   = calc
CXX      = clang++
JAR      = ../lib/antlr-4.9-complete.jar
MODE    ?= debug
OUTDIR   = ../build/$(MODE)
CXXFLAGS = -std=c++17 -pthread -I/usr/include/antlr4-runtime -Wno-attributes
LDLIBS   = -lantlr4-runtime
SRCS     = main.cpp ast.cpp builder.cpp
GEN      = GrammarLexer.cpp GrammarParser.cpp GrammarBaseVisitor.cpp

ifeq ($(MODE),release)
CXXFLAGS += -O2 -DNDEBUG
else ifeq ($(MODE),debug)
CXXFLAGS += -g -O0
else
$(error MODE must be debug or release)
endif

.DEFAULT_GOAL := all

FORMAT_FILES = $(filter-out Grammar%,$(wildcard *.cpp *.h))

# format first (skipped if clang-format is missing), then build
all:
	@$(MAKE) --no-print-directory format
	@$(MAKE) --no-print-directory $(OUTDIR)/$(TARGET)

format:
	@if command -v clang-format >/dev/null; then clang-format -i $(FORMAT_FILES); \
	else echo "clang-format not found, skipping format"; fi

antlr: $(GEN)

$(OUTDIR)/$(TARGET): $(SRCS) $(wildcard *.h) $(GEN)
	@mkdir -p $(OUTDIR)
	$(CXX) $(CXXFLAGS) $(SRCS) $(GEN) -o $@ $(LDLIBS)

$(GEN): Grammar.g4
	java -jar $(JAR) -Dlanguage=Cpp -visitor -no-listener -Xexact-output-dir -o . Grammar.g4

.PHONY: all antlr format clean
clean:
	rm -rf ../build
	rm -f Grammar*.cpp Grammar*.h Grammar*.interp Grammar*.tokens
