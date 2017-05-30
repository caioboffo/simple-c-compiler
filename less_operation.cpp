#include "less_operation.hpp"

void less_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " < ";
  right->print();
  std::cout << ")";
}

void less_operation::evaluate() {
  std::cout << "evaluating a < operation ...\n";
}
