#include "ast.h"
#include <ostream>
#include <sstream>

std::string Num::to_string() const
{
  std::ostringstream os;
  os << value;
  return os.str();
}

std::string Neg::to_string() const
{
  return "(neg " + operand->to_string() + ")";
}

std::string Bin::to_string() const
{
  return std::string("(") + op + " " + lhs->to_string() + " " +
         rhs->to_string() + ")";
}

std::string Expr::to_string() const
{
  return std::visit([](const auto &n) { return n.to_string(); }, node);
}

std::ostream &operator<<(std::ostream &os, const Expr &e)
{
  return os << e.to_string();
}
