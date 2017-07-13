#include "equal_operation.hpp"
#include "error_manager.hpp"

void equal_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " == ";
  right->print();
  std::cout << ")";
}

void equal_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating == operation\n";
  #endif

  this->left->evaluate();
  this->right->evaluate();

  if (this->left->type  == this->right->type) {
    this->type = basic_type::BOOLEAN;
    this->value = this->left->value == this->right->value;
  }
  else
    error_manager::error("incompatible types", this->locations);  

}
