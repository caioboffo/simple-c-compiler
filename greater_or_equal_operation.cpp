#include "greater_or_equal_operation.hpp"

void greater_or_equal_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " >= ";
  right->print();
  std::cout << ")";
}

void greater_or_equal_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating >= operation\n";
  #endif 
}
