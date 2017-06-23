#include <iostream>
#include "expression.hpp"
#include "return_stmt.hpp"

void return_stmt::print() {
  std::cout << "return ";
  if (return_expression)
    return_expression->print();
}

void return_stmt::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a return statement\n";
  #endif

}
