#ifndef GREATER_OPERATION_H
#define GREATER_OPERATION_H

#include <iostream>
#include "operation.hpp"
#include "codegen_context.hpp"

using namespace llvm;

class greater_operation : public operation {
public:
  greater_operation(tree_node *l, tree_node *r, YYLTYPE loc)
    : operation(l, r, loc) {} 
  void print();
  void evaluate();
  Value *emit_ir_code(codegen_context *context);
};


#endif /* GREATER_OPERATION_H */
