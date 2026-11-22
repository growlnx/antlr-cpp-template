#pragma once
#include "antlr4-runtime.h"
#include "ast.h"

// parse tree -> AST
ExprPtr build_ast(antlr4::tree::ParseTree *tree);
