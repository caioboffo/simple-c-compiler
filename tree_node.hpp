#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <iostream>
#include <string>
#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include "locations.hpp"

class tree_node {
public:
  static llvm::Module *module;
  tree_node *parent;
  YYLTYPE locations;
  virtual void print() {}
  virtual void evaluate() {}
  virtual llvm::Value *emit_ir_code() {}
  tree_node() {}
  tree_node(YYLTYPE loc) : locations(loc) {}
};

#endif /* TREE_NODE_H */
