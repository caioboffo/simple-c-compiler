#include "over_operation.hpp"

void over_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " / ";
  right->print();
  std::cout << ")";
}

void over_operation::evaluate() {
  std::cout << "evaluating a / operation ...\n";
}