#ifndef RETURN_STMT_H
#define RETURN_STMT_H

#include "statement.hpp"
#include "codegen_context.hpp"

class tree_node;

using namespace llvm;

class return_stmt : public statement {
protected:
  expression *return_expression;
public:
  return_stmt(YYLTYPE loc) {
    this->locations = loc;
  }
  return_stmt(tree_node *re, YYLTYPE loc) {
    return_expression = static_cast<expression*>(re);
    this->locations = loc;
  }
    
  void print();
  void evaluate();
  Value *emit_ir_code(codegen_context *context);
};

#endif /* RETURN_STMT_H */
