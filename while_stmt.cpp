#include <iostream>
#include "while_stmt.hpp"
#include "error_manager.hpp"
#include "expression.hpp"
#include "basic_block.hpp"

void while_stmt::print() {
  std::cout << "while ";
  exp->print();
  std::cout << "\n";
  block->print();
}

void while_stmt::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a while statement\n";
  #endif
  
  exp->evaluate();
  
  if (exp->type != basic_type::BOOLEAN)
    error_manager::error("while expression should be a logic expression",
                         this->locations);

  this->return_type 
    = static_cast<basic_block*>(this->parent)->return_type;

  if (block) {
    block->return_type = this->return_type;
    block->evaluate();
    static_cast<basic_block*>(this->parent)->return_stmt
      = block->return_stmt;
  }
}
