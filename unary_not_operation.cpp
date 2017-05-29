#include "unary_not_operation.hpp"
#include "expression.hpp"

void unary_not_operation::print() {
  std::cout << "!";
  exp->print();
}

int unary_not_operation::evaluate() {
  std::cout << "evaluating a unary not operation ...\n";
  value = !(exp->evaluate());
}
