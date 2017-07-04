#include "expression.hpp"
#include "assignment.hpp"
#include "symbol.hpp"
#include "tree_node.hpp"
#include "symbol_table.hpp"
#include "error_manager.hpp"

void assignment::print() {
  id->print();
  std::cout << " = ";
  exp->print();
}

void assignment::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating an assignment\n";
  #endif
  
  id->evaluate();
  if (id->type != basic_type::ERROR) {
    exp->evaluate();

    if (id->type != exp->type) {
      std::string err
        = "assingment for variable " + id->id
        + " should be of type " + to_string(id->type);
      error_manager::error(err.c_str(), this->locations);
    }
  }
}
