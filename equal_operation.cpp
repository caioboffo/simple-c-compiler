#include "equal_operation.hpp"

void equal_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " == ";
  right->print();
  std::cout << ")";
}

void equal_operation::evaluate() {
  std::cout << "evaluating a == operation ...\n";
}
