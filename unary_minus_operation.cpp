#include "unary_minus_operation.hpp"
#include "expression.hpp"

void unary_minus_operation::print() {
  std::cout << "-";
  exp->print();
}

int unary_minus_operation::evaluate() {
  std::cout << "evaluating a unary minus operation...\n";
  value = -(exp->evaluate());
}
