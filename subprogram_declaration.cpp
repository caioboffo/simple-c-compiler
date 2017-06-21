#include <iostream>
#include "subprogram_declaration.hpp"

subprogram_declaration::subprogram_declaration
                       (std::string            id,
                        std::list<tree_node*> *parameters,
                        tree_node             *compound_statement) {
  this->name   = new symbol(id);
  this->params = parameters;
  this->block  = compound_statement;
  
}

subprogram_declaration::subprogram_declaration
                       (basic_type            t,
                        std::string            id,
                        std::list<tree_node*> *parameters,
                        tree_node             *compound_statement) {
  
  this->return_type = t;
  subprogram_declaration(id, parameters, compound_statement);

}

void subprogram_declaration::print() {
  std::cout << "it's me function" << "\n";
}

void subprogram_declaration::evaluate() {
  #ifdef STATUS_OUTPUT 
  std::cout << "evaluating a procedure declaration " << "\n";
  #endif
  // evaluate each parameter 
  if (this->params->size() > 0) {
    for (auto param = params->begin(); param != params->end(); param++) {
      (*param)->evaluate();
    }
  }

  // evaluate the procedure block
  block->evaluate();
}
