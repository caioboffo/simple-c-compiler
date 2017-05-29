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

int ternary_if_operation::evaluate() {
  std::cout << "evaluating a ternary if expression...\n";
  if (condition->evaluate()) {
    value = then_branch->evaluate();
  } else {
    value = else_branch->evaluate();
  }
  return value;
}
