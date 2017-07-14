#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <iostream>
#include <string>
#include <llvm/IR/Value.h>
#include "locations.hpp"

using namespace llvm;

class codegen_context;

class tree_node {
public:
  tree_node *parent;
  YYLTYPE locations;
  virtual void print() {}
  virtual void evaluate() {}
  virtual Value *emit_ir_code(codegen_context *context) {}
  tree_node() {}
  tree_node(YYLTYPE loc) : locations(loc) {}
};

#endif /* TREE_NODE_H */
