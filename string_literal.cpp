#include "string_literal.hpp"

void string_literal::print() {
  if (string_value.length()) 
    std::cout << string_value ;
  else
    std::cout << "NULL";
}

int string_literal::evaluate() {
  std::cout << "evaluating a string literal...\n";
  return 1;
}
