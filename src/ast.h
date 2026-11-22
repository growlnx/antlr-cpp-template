#pragma once
#include <iosfwd>
#include <memory>
#include <string>
#include <variant>

// AST: Num | Neg | Bin
struct Expr;
using ExprPtr = std::shared_ptr<Expr>;

struct Num
{
  double value;
  std::string to_string() const;
};

struct Neg
{
  ExprPtr operand;
  std::string to_string() const;
};

struct Bin
{
  char op;
  ExprPtr lhs, rhs;
  std::string to_string() const;
};

struct Expr
{
  std::variant<Num, Neg, Bin> node;
  std::string to_string() const; // S-expression, e.g. (+ 1 (* 2 3))
};

template <class T> ExprPtr make(T n)
{
  return std::make_shared<Expr>(Expr{std::move(n)});
}

std::ostream &operator<<(std::ostream &os, const Expr &e);
