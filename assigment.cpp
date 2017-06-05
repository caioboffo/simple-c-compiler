#include "expression.hpp"
#include "assigment.hpp"
#include "identifier.hpp"
#include "tree_node.hpp"

void assigment::print() {
  id->print();
  std::cout << " = ";
  exp->print();
  std::cout << std::endl;
}

void assigment::evaluate() {
  // lookup the identifier in the tableId and change its value
}
