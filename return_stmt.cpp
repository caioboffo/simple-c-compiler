#include <iostream>
#include "expression.hpp"
#include "return_stmt.hpp"
#include "basic_block.hpp"
#include "error_manager.hpp"

void return_stmt::print() {
  std::cout << "return ";
  if (return_expression)
    return_expression->print();
}

void return_stmt::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a return statement\n";
  #endif

  static_cast<basic_block*>(this->parent)->return_stmt = true;
  
  if (return_expression) {
    return_expression->evaluate();
    this->return_type = return_expression->type;
  } else
    this->return_type = basic_type::VOID;

  if (static_cast<basic_block*>(this->parent)->return_type
      != this->return_type) {
    std::string err = "cannot convert "
      + to_string(this->return_type) + " to "
      + to_string(static_cast<basic_block*>(this->parent)->return_type);
    error_manager::error(err.c_str(), this->locations);
  }
}
