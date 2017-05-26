#include "boolean.hpp"

void boolean::print() {
  if (value)
    std::cout << "true" ;
  else
    std::cout << "false" ;
}

int boolean::evaluate() {
  std::cout << "evaluating a boolean type ...\n";
  return value;
}

