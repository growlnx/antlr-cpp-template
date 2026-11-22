#include "GrammarLexer.h"
#include "GrammarParser.h"
#include "antlr4-runtime.h"
#include "ast.h"
#include "builder.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

// parses one input and prints its AST; false on syntax/runtime error
static bool run(antlr4::ANTLRInputStream &in)
{
  GrammarLexer lexer(&in);
  antlr4::CommonTokenStream toks(&lexer);
  GrammarParser parser(&toks);

  auto *tree = parser.program();
  if (parser.getNumberOfSyntaxErrors() > 0)
    return false;

  try
  {
    std::cout << *build_ast(tree) << "\n";
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << "\n";
    return false;
  }
  return true;
}

static int run_file(const char *path)
{
  std::ifstream f(path);

  if (!f)
  {
    std::cerr << "failed to open " << path << "\n";
    return 1;
  }

  antlr4::ANTLRInputStream in(f);
  return run(in) ? 0 : 1;
}

// one expression per line; Ctrl-D exits
static int repl()
{
  const bool tty = isatty(STDIN_FILENO);
  std::string line;

  while (true)
  {
    if (tty)
      std::cout << "> " << std::flush;
    if (!std::getline(std::cin, line))
      break;
    if (line.empty())
      continue;

    antlr4::ANTLRInputStream in(line);
    run(in);
  }
  if (tty)
    std::cout << "\n";
  return 0;
}

int main(int argc, char **argv)
{
  return argc >= 2 ? run_file(argv[1]) : repl();
}
