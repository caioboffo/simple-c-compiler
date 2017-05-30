#include "or_operation.hpp"

void or_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " || ";
  right->print();
  std::cout << ")";
}

void or_operation::evaluate() {
  std::cout << "evaluating a || operation ...\n";
}
