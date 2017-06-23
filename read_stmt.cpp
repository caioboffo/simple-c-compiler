#include <iostream>
#include "read_stmt.hpp"

void read_stmt::print() {
  std::cout << "read ";
  var->print();
}

void read_stmt::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a read statement\n";
  #endif
}
