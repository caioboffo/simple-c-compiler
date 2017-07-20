#ifndef UNARY_NOT_OPERATION_H
#define UNARY_NOT_OPERATION_H

#include <iostream>
#include "operation.hpp"
#include "codegen_context.hpp"

class expression;

using namespace llvm;

class unary_not_operation : public operation {
protected:
  expression *exp;
public:
  unary_not_operation(tree_node *exp, YYLTYPE loc) {
    this->exp = static_cast<expression*>(exp);
    this->locations = loc;
  }
  void print();
  void evaluate();
  Value *emit_ir_code(codegen_context *context);
};

#endif /* UNARY_NOT_OPERATION_H */
