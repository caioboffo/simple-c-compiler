#include "number.hpp"

number::number(int v, YYLTYPE loc) {
  this->value = v;
  set_type(basic_type::INTEGER);
  this->locations = loc;
}

void number::print() {
  std::cout << value ;
}

void number::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating number " << value << "\n";
  #endif
}
