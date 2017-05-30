#include "not_equal_operation.hpp"

void not_equal_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " != ";
  right->print();
  std::cout << ")";
}

void not_equal_operation::evaluate() {
  std::cout << "evaluating a != operation ...\n";
}
