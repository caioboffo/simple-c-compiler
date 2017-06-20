#include "expression.hpp"
#include "assignment.hpp"
#include "symbol.hpp"
#include "tree_node.hpp"

void assignment::print() {
  id->print();
  std::cout << " = ";
  exp->print();
  std::cout << std::endl;
}

void assignment::evaluate() {
  std::cout << "evaluating an assignment\n";
  exp->evaluate();
}
