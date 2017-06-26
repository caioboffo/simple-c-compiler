#include <iostream>
#include "if_stmt.hpp"

void if_stmt::print() {
  std::cout << "if ";
  exp->print();
  std::cout << "\n";
  then_block->print();
  if (else_block) {
    std::cout << "\n";
    else_block->print();
  }
}

void if_stmt::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a if statement\n";
  #endif
}

