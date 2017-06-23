#include <iostream>
#include "subprogram_declaration.hpp"

subprogram_declaration::subprogram_declaration
                       (std::string            id,
                        std::list<tree_node*> *parameters,
                        tree_node             *compound_statement) {
  
  this->name   = new symbol(id);
  this->param_list = parameters;
  this->block = static_cast<basic_block*>(compound_statement);
  
}

subprogram_declaration::subprogram_declaration
                       (basic_type             t,
                        std::string            id,
                        std::list<tree_node*> *parameters,
                        tree_node             *compound_statement) {

  this->return_type = t;
  this->name   = new symbol(id);
  this->param_list = parameters;
  this->block = static_cast<basic_block*>(compound_statement);

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

  // evaluate each parameter
  if (param_list->size() > 0) {
    for (auto param = param_list->begin();
         param != param_list->end();
         param++) {
      (*param)->evaluate();
    }
  }

  // evaluate the subprogram block
  block->evaluate();
}
