#include "greater_or_equal_operation.hpp"

void greater_or_equal_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " >= ";
  right->print();
  std::cout << ")";
}

void greater_or_equal_operation::evaluate() {
  std::cout << "evaluating a >= operation ...\n";
}
