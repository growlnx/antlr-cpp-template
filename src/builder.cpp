#include "builder.h"
#include "GrammarBaseVisitor.h"
#include "GrammarParser.h"

namespace
{
struct Builder : GrammarBaseVisitor
{
  ExprPtr build(antlr4::tree::ParseTree *t) { return visit(t).as<ExprPtr>(); }

  antlrcpp::Any visitProgram(GrammarParser::ProgramContext *c) override
  {
    return build(c->expr());
  }

  antlrcpp::Any visitParen(GrammarParser::ParenContext *c) override
  {
    return build(c->expr()); // parentheses do not exist in the AST
  }

  antlrcpp::Any visitNum(GrammarParser::NumContext *c) override
  {
    return make(Num{std::stod(c->NUMBER()->getText())});
  }

  antlrcpp::Any visitNeg(GrammarParser::NegContext *c) override
  {
    return make(Neg{build(c->expr())});
  }

  antlrcpp::Any visitPow(GrammarParser::PowContext *c) override
  {
    return make(Bin{'^', build(c->expr(0)), build(c->expr(1))});
  }

  antlrcpp::Any visitMulDiv(GrammarParser::MulDivContext *c) override
  {
    return make(Bin{c->op->getText()[0], build(c->expr(0)), build(c->expr(1))});
  }

  antlrcpp::Any visitAddSub(GrammarParser::AddSubContext *c) override
  {
    return make(Bin{c->op->getText()[0], build(c->expr(0)), build(c->expr(1))});
  }
};
} // namespace

ExprPtr build_ast(antlr4::tree::ParseTree *tree)
{
  return Builder().visit(tree).as<ExprPtr>();
}
