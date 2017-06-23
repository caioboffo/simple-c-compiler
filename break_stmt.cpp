#include <iostream>
#include "break_stmt.hpp"

void break_stmt::print() {
  std::cout << "break ";
}

void break_stmt::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a break \n";
  #endif 
}
