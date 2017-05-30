#include "module_operation.hpp"

void module_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " % ";
  right->print();
  std::cout << ")";
}

void module_operation::evaluate() {
  std::cout << "evaluating a % operation ...\n";
}
