#include <iostream>
#include "write_stmt.hpp"

void write_stmt::print() {
  std::cout << "write ";
  int index = 1;
  for (auto it = expressions->begin();
       it != expressions->end();
       it++, index++) {
    (*it)->print();
    if (index != expressions->size())
      std::cout << ", ";
  }
}

void write_stmt::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating write statement\n";
  #endif
}
