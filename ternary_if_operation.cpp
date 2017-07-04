#include "ternary_if_operation.hpp"
#include "error_manager.hpp"

void ternary_if_operation::print() {
  std::cout << "(";
  condition->print();
  std::cout << ") ? ";
  then_branch->print();
  std::cout << " : ";
  else_branch->print();
  std::cout << std::endl;
}

void ternary_if_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a ternary if expression...\n";
  #endif

  condition->evaluate();
  if (condition->type != basic_type::BOOLEAN)
    error_manager::error("ternary operator condition should be boolean"
                         , this->locations);

  then_branch->evaluate();
  else_branch->evaluate();

  // not sure if I'd leave this or remove it
  if (condition->value) {
    this->type = then_branch->type;
  }
  else {
    this->type = else_branch->type;
  }
                    

  


}
