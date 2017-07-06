#include <iostream>
#include "subprogram_declaration.hpp"
#include "symbol_table.hpp"
#include "error_manager.hpp"

subprogram_declaration::subprogram_declaration
                       (basic_type             t,
                        std::string            id,
                        std::list<tree_node*> *parameters,
                        tree_node             *compound_statement,
                        YYLTYPE loc) {

  this->return_type = t;
  this->name   = new symbol(id);
  this->param_list = parameters;
  this->block = static_cast<basic_block*>(compound_statement);
  this->locations = loc;

}

subprogram_declaration::subprogram_declaration
                       (std::string            id,
                        std::list<tree_node*> *parameters,
                        tree_node             *compound_statement,
                        YYLTYPE loc) {

  this->return_type = basic_type::VOID;
  this->name   = new symbol(id);
  this->param_list = parameters;
  this->block = static_cast<basic_block*>(compound_statement);
  this->locations = loc;
                         
  
}

void subprogram_declaration::print() {
  switch (return_type) {
    case basic_type::INTEGER : {
      std::cout << "int ";
      break;
    }
    case basic_type::BOOLEAN : {
      std::cout << "bool ";
      break;
    }
    case basic_type::STRING : {
      std::cout << "string ";
      break;
    }
    default:
      break;
  }

  name->print();
  std::cout <<  "(";
  int i = 1;
  if (param_list->size() > 0) {
    for (auto param = param_list->begin();
         param != param_list->end();
         param++, i++) {
      (*param)->print();
      if (i != param_list->size())
        std::cout << ", ";
    }
  }
  std::cout << ") \n";

  block->print();
}

void subprogram_declaration::evaluate() {
  #ifdef STATUS_OUTPUT 
  std::cout << "evaluating subprogram declaration\n";
  #endif

  if (this->return_type == basic_type::VOID) { 
    symbol_table::insert(this->name->id,
                         basic_type::PROCEDURE,
                         basic_type::VOID,
                         this->param_list,
                         this->locations);
  } else {
    symbol_table::insert(this->name->id,
                         basic_type::FUNCTION,
                         this->return_type,
                         this->param_list,
                         this->locations);

  }

  symbol_table::create_scope();

  // evaluate each parameter so it can be inserted to symbol table
  if (param_list->size() > 0) {
    for (auto param = param_list->begin();
         param != param_list->end();
         param++) {
      (*param)->evaluate();
    }
  }

  // evaluate the subprogram block
  block->return_type = this->return_type;
  block->parent = this;
  block->evaluate();

  if (!block->return_stmt && this->return_type != basic_type::VOID) {
    std::string err = "missing return statement for function "
      + this->name->id;
    error_manager::error(err.c_str(), this->locations);
  }

  symbol_table::delete_scope();
}
