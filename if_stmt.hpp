#ifndef IF_STMT_H
#define IF_STMT_H

#include "statement.hpp"
#include "codegen_context.hpp"

class expression;
class basic_block;

using namespace llvm;
class if_stmt : public statement {
protected:
  expression *exp;
  basic_block *then_block, *else_block;
public:
  if_stmt(tree_node *exp,
          tree_node *then_block,
          YYLTYPE loc,
          tree_node *else_block = NULL);
    
  void print();
  void evaluate();
  Value *emit_ir_code(codegen_context *context);
};

#endif /* IF_STMT_H */
