#include "greater_operation.hpp"

void greater_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " > ";
  right->print();
  std::cout << ")";
}

void greater_operation::evaluate() {
  std::cout << "evaluating a > operation ...\n";
}
