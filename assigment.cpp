#include "expression.hpp"
#include "assigment.hpp"

void assigment::print() {
  std::cout << id << " = ";
  exp->print();
  std::cout << std::endl;
}

void assigment::evaluate() {
}
