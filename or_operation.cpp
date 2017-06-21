#include "or_operation.hpp"

void or_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " || ";
  right->print();
  std::cout << ")";
}

void or_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating || operation\n";
  #endif
}
