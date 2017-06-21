#include "equal_operation.hpp"

void equal_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " == ";
  right->print();
  std::cout << ")";
}

void equal_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating == operation\n";
  #endif
}
