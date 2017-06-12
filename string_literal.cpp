#include "string_literal.hpp"

string_literal::string_literal(std::string str) {
  string_value = str;
  set_type(30);
}

void string_literal::print() {
  if (string_value.length()) 
    std::cout << string_value ;
  else
    std::cout << "NULL";
}

void string_literal::evaluate() {
  std::cout << "evaluating a string literal...\n";
}
