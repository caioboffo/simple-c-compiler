#include "unary_minus_operation.hpp"
#include "expression.hpp"

void unary_minus_operation::print() {
  std::cout << "-";
  exp->print();
}

void unary_minus_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a unary minus operation\n";
  #endif
}
