#include "number.hpp"

void number::print() {
  std::cout << value ;
}

int number::evaluate() {
  std::cout << "evaluating number...\n";
  return value;
}
