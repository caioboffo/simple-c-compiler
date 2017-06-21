#include "number.hpp"

void number::print() {
  std::cout << value ;
}

void number::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating number " << value << "\n";
  #endif
}
