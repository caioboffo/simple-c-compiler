#ifndef MINUS_OPERATION_H
#define MINUS_OPERATION_H

#include <iostream>
#include "operation.hpp"
#include "codegen_context.hpp"

using namespace llvm;

class minus_operation : public operation {
public:
  minus_operation(tree_node *l, tree_node *r, YYLTYPE loc)
    : operation(l, r, loc) {} 
  void print();
  void evaluate();
  Value *emit_ir_code(codegen_context *context);
};


#endif /* MINUS_OPERATION_H */
