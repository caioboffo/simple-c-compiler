#include "expression.hpp"
#include "assignment.hpp"
#include "symbol.hpp"
#include "tree_node.hpp"

void assignment::print() {
  id->print();
  std::cout << " = ";
  exp->print();
}

void assignment::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating an assignment\n";
  #endif
  exp->evaluate();
}
