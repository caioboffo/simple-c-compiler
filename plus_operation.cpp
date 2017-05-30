#include "plus_operation.hpp"

void plus_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " + ";
  right->print();
  std::cout << ")";
}

void plus_operation::evaluate() {
  std::cout << "evaluating a + operation ...\n";
}
