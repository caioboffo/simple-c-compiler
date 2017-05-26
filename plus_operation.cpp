#include "plus_operation.hpp"

void plus_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " + ";
  right->print();
  std::cout << ")";
}

int plus_operation::evaluate() {
  std::cout << "evaluating a + operation ...\n";
  int left_num, right_num;
  
  left_num = left->evaluate();
  right_num = right->evaluate();
  value = left_num + right_num;
  
  return value;
}
