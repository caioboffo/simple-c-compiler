#include "not_equal_operation.hpp"

void not_equal_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " != ";
  right->print();
  std::cout << ")";
}

void not_equal_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating != operation\n";
  #endif
}
