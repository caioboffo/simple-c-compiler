#include "ternary_if_operation.hpp"

void ternary_if_operation::print() {
  std::cout << "(";
  condition->print();
  std::cout << ") ? ";
  then_branch->print();
  std::cout << " : ";
  else_branch->print();
  std::cout << std::endl;
}

void ternary_if_operation::evaluate() {
  std::cout << "evaluating a ternary if expression...\n";
}
