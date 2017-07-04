#include "over_operation.hpp"
#include "error_manager.hpp"

void over_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " / ";
  right->print();
  std::cout << ")";
}

void over_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating / operation\n";
  #endif

  this->left->evaluate();
  this->right->evaluate();

  if (this->left->type  == basic_type::INTEGER &&
      this->right->type == basic_type::INTEGER)
    this->type = basic_type::INTEGER;
  else
    error_manager::error("incompatible types", this->locations);
  
  if (this->right->value == 0)
    error_manager::error("division by zero", this->right->locations);
}
