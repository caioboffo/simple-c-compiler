#include "unary_not_operation.hpp"
#include "expression.hpp"
#include "error_manager.hpp"

void unary_not_operation::print() {
  std::cout << "!";
  exp->print();
}

void unary_not_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a unary not operation\n";
  #endif

  exp->evaluate();

  if (exp->type == basic_type::BOOLEAN)
    this->type = exp->type;
  else
    error_manager::error("incompatible types", this->locations);  

}
