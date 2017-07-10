#include <iostream>
#include "if_stmt.hpp"
#include "error_manager.hpp"
#include "expression.hpp"
#include "basic_block.hpp"

if_stmt::if_stmt(tree_node *exp,
                 tree_node *then_block,
                 YYLTYPE loc,
                 tree_node *else_block) {
  this->exp = static_cast<expression*>(exp);
  this->then_block = static_cast<basic_block*>(then_block);
  this->else_block = static_cast<basic_block*>(else_block);
  this->locations = loc;
}

void if_stmt::print() {
  std::cout << "if ";
  exp->print();
  std::cout << "\n";
  then_block->print();
  if (else_block) {
    std::cout << "\n";
    else_block->print();
  }
}

void if_stmt::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating an if statement\n";
  #endif

  exp->evaluate();
  
  if (this->exp->type != basic_type::BOOLEAN)
    error_manager::error("if expression should be a logic expression",
                         this->locations);

  this->return_type 
    = static_cast<basic_block*>(this->parent)->return_type;

  #ifdef RETURN_STATUS
  std::cout << "if stmt returns " << to_string(this->return_type) << "\n";
  #endif

  this->then_block->return_type = this->return_type;
  then_block->evaluate();

  if (else_block) {
    this->else_block->return_type = this->return_type;
    else_block->evaluate();

    if ((then_block->return_stmt && else_block->return_stmt) 
        && (then_block->return_type == else_block->return_type)) {
      static_cast<basic_block*>(this->parent)->return_stmt
        = then_block->return_stmt;
    }
  }
}

