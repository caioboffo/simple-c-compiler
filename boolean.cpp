#include "boolean.hpp"

void boolean::print() {
  if (value)
    std::cout << "true" ;
  else
    std::cout << "false" ;
}

void boolean::evaluate() {
  std::cout << "evaluating a boolean type ...\n";
}

