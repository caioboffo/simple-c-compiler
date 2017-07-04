#include "minus_operation.hpp"
#include "error_manager.hpp"

void minus_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " - ";
  right->print();
  std::cout << ")";
}

void minus_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating - operation\n";
  #endif

  this->left->evaluate();
  this->right->evaluate();

  if (this->left->type  == basic_type::INTEGER &&
      this->right->type == basic_type::INTEGER)
    this->type = basic_type::INTEGER;
  else
    error_manager::error("incompatible types", this->locations);
}
