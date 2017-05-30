#include "less_or_equal_operation.hpp"

void less_or_equal_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " <= ";
  right->print();
  std::cout << ")";
}

void less_or_equal_operation::evaluate() {
  std::cout << "evaluating a <= operation ...\n";
}
