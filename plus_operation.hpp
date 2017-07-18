#ifndef PLUS_OPERATION_H
#define PLUS_OPERATION_H

#include <iostream>
#include "operation.hpp"
#include "codegen_context.hpp"

using namespace llvm;

class plus_operation : public operation {
public:
  plus_operation(tree_node *l, tree_node *r, YYLTYPE loc) :
    operation(l, r, loc) {}
  void print();
  void evaluate();
  Value *emit_ir_code(codegen_context *context);
};

#endif /* PLUS_OPERATION_H */
