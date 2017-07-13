#include <iostream>
#include <llvm/IR/LLVMContext.h>
#include "abstract_syntax_tree.hpp"
#include "error_manager.hpp"

llvm::Module *tree_node::module;

std::string base_name(std::string const & path)
{
  return path.substr(path.find_last_of("/\\") + 1);
}

abstract_syntax_tree::abstract_syntax_tree(std::list<tree_node*> *nodelist)
{
  nodes = nodelist;
  tree_node::module = new llvm::Module(
                                base_name(error_manager::filename) + ".bc",
                                llvm::getGlobalContext());
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

llvm::Value *abstract_syntax_tree::emit_ir_code() {
  std::list<tree_node*>::iterator nodelist_iterator;
  for (nodelist_iterator = nodes->begin();
       nodelist_iterator != nodes->end();
       nodelist_iterator++) {
    (*nodelist_iterator)->emit_ir_code();
  }
}
