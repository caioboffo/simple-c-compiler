#include "identifier.hpp"
#include "string_literal.hpp"
#include "boolean.hpp"
#include "number.hpp"

void identifier::set_type(int t) {
  this->type = t;

  // use this code only when debug_output is enabled
  if (initializer == NULL) {
    switch (type) {
    case 10: {
      initializer = new number(0);
      break;
    }
    case 20: {
      initializer = new boolean(0);
      break;
    }
    case 30: {
      initializer = new string_literal("");
      break;
    }
    default:
      break;
    }
  }
  
}

void identifier::print() {
  std::cout << id << " = ";
  initializer->print();
  std::cout << std::endl;
}

int identifier::evaluate() {
  std::cout << "evaluating identifier ...\n" ;
  if (size) evaluated_size = size->evaluate();
  if (initializer) value = initializer->evaluate();
  return value;
}

