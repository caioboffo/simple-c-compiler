#include <iostream>
#include "while_stmt.hpp"
#include "error_manager.hpp"
#include "expression.hpp"
#include "basic_block.hpp"
#include "symbol_table.hpp"

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
  
  #ifdef RETURN_STATUS
  std::cout << "while stmt returns " << to_string(this->return_type) << "\n";
  #endif

  block->return_type = this->return_type;
  
  symbol_table::create_scope();
  block->evaluate();
  symbol_table::delete_scope();
  
  static_cast<basic_block*>(this->parent)->return_stmt
    = block->return_stmt;

}
