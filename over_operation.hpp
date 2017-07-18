#ifndef OVER_OPERATION_H
#define OVER_OPERATION_H

#include <iostream>
#include "operation.hpp"
#include "codegen_context.hpp"

using namespace llvm;

class over_operation : public operation {
public:
  over_operation(tree_node *l, tree_node *r, YYLTYPE loc)
    : operation(l, r, loc) {} 
  void print();
  void evaluate();
  Value* emit_ir_code(codegen_context *context);
};

#endif /* OVER_OPERATION_H */
