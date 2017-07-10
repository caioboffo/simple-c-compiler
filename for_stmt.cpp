#include <iostream>
#include "for_stmt.hpp"
#include "expression.hpp"
#include "basic_block.hpp"
#include "error_manager.hpp"

void for_stmt::print() {
  std::cout << "for (";
  first_assign->print();
  std::cout << ", ";
  exp->print();
  std::cout << ", ";
  second_assign->print();
  std::cout << ")\n";
  block->print();
}

void for_stmt::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating  a for statement\n";
  #endif
  
  first_assign->evaluate();
  
  exp->evaluate();
  if (static_cast<expression*>(exp)->type != basic_type::BOOLEAN)
    error_manager::error("for expression should be a logic expression",
                         this->locations);

  this->return_type 
    = static_cast<basic_block*>(this->parent)->return_type;

  #ifdef RETURN_STATUS
  std::cout << "for stmt returns " << to_string(this->return_type) << "\n";
  #endif
  
  second_assign->evaluate();

  if (block) {
    static_cast<basic_block*>(block)->return_type = this->return_type;
    block->evaluate();
    static_cast<basic_block*>(this->parent)->return_stmt
      = static_cast<basic_block*>(block)->return_stmt;
  }
  
}
