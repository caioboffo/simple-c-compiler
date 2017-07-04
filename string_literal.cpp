#include "string_literal.hpp"
#include "basic_type.hpp"

string_literal::string_literal(std::string str) {
  this->string_value = str;
  set_type(basic_type::STRING);
}

string_literal::string_literal(std::string str, YYLTYPE loc) {
  this->string_value = str;
  set_type(basic_type::STRING);
  this->locations = loc;
}
void string_literal::print() {
  if (string_value.length()) 
    std::cout << this->string_value ;
  else
    std::cout << "NULL";
}

void string_literal::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a string literal " << this->string_value << "\n";
  #endif
}
