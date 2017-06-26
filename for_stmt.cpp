#include <iostream>

#include "for_stmt.hpp"
#include "expression.hpp"

void for_stmt::print() {
  std::cout << "for (";
  first_assign->print();
  std::cout << ", ";
  exp->print();
  std::cout << ", ";
  second_assign->print();
  std::cout << ")\n";
  block->print();
}

void for_stmt::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating  a for statement\n";
  #endif
}
