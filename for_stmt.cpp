#include <iostream>
#include "for_stmt.hpp"
#include "expression.hpp"
#include "basic_block.hpp"
#include "error_manager.hpp"
#include "symbol_table.hpp"

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

  symbol_table::push_accept_break();
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


  static_cast<basic_block*>(block)->return_type = this->return_type;

  symbol_table::create_scope();
  block->evaluate();
  symbol_table::delete_scope();
  
  static_cast<basic_block*>(this->parent)->return_stmt
    = static_cast<basic_block*>(block)->return_stmt;

  symbol_table::pop_accept_break();
}
