#include "over_operation.hpp"

void over_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " / ";
  right->print();
  std::cout << ")";
}

void over_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating / operation\n";
  #endif
}
