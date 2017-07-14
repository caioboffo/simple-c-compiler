#ifndef ABSTRACT_SYNTAX_TREE_H
#define ABSTRACT_SYNTAX_TREE_H

#include <list>
#include <stack>
#include <llvm/IR/Module.h>
#include "codegen_context.hpp"
#include "tree_node.hpp"

using namespace llvm;

class abstract_syntax_tree : public tree_node {
  
  codegen_context *context;
  std::list<tree_node*> *nodes;

public:

  abstract_syntax_tree(std::list<tree_node*> *nodelist);
  Module *get_module();
  void evaluate();
  Value *emit_ir_code(codegen_context *context);
  
};

#endif /* ABSTRACT_SYNTAX_TREE_H */
