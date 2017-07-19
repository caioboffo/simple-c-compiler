#include <iostream>
#include <llvm/IR/LLVMContext.h>
#include "abstract_syntax_tree.hpp"
#include "error_manager.hpp"
#include "core_functions.hpp"

abstract_syntax_tree::abstract_syntax_tree(std::list<tree_node*> *nodelist)
{
  nodes = nodelist;
  context = new codegen_context();
}

Module *abstract_syntax_tree::get_module() {
  return context->module;
}

void abstract_syntax_tree::evaluate() {
  std::list<tree_node*>::iterator nodelist_iterator;
  for (nodelist_iterator = nodes->begin();
       nodelist_iterator != nodes->end();
       nodelist_iterator++) {
    (*nodelist_iterator)->evaluate();
    #if defined SOURCE_OUTPUT
    (*nodelist_iterator)->print();
    std::cout << "\n";
    #endif
  }
}

Value *abstract_syntax_tree::emit_ir_code(codegen_context *context) {
  
  std::list<tree_node*>::iterator nodelist_iterator;
  Value *last;
  for (nodelist_iterator = nodes->begin();
       nodelist_iterator != nodes->end();
       nodelist_iterator++) {
    last = (*nodelist_iterator)->emit_ir_code(this->context);
  }

  create_core_functions(this->context);
  return last;
}
