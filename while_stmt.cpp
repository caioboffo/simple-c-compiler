#include <iostream>
#include "while_stmt.hpp"

void while_stmt::print() {
  std::cout << "while ";
  exp->print();
  std::cout << "\n";
  block->print();
}

void while_stmt::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a while statement\n";
  #endif
  
  if (exp)
    this->exp->evaluate();

  if (block)
    block->evaluate();

}
