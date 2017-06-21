#include "minus_operation.hpp"

void minus_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " - ";
  right->print();
  std::cout << ")";
}

void minus_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating - operation\n";
  #endif
}
