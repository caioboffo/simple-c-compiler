#ifndef ABSTRACT_SYNTAX_TREE_H
#define ABSTRACT_SYNTAX_TREE_H

#include <list>
#include <llvm/IR/Module.h>
#include "tree_node.hpp"

class abstract_syntax_tree : public tree_node {
  std::list<tree_node*> *nodes;

public:
  abstract_syntax_tree(std::list<tree_node*> *nodelist);
  void evaluate();
  llvm::Value *emit_ir_code();
};

#endif /* ABSTRACT_SYNTAX_TREE_H */
