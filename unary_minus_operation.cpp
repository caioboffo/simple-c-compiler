#include "unary_minus_operation.hpp"
#include "expression.hpp"
#include "error_manager.hpp"

void unary_minus_operation::print() {
  std::cout << "-";
  exp->print();
}

void unary_minus_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a unary minus operation\n";
  #endif

  exp->evaluate();

  if (exp->type == basic_type::INTEGER) {
    this->type = exp->type;
    this->value = -this->value;
  }
  else
    error_manager::error("incompatible types", this->locations);  

}
