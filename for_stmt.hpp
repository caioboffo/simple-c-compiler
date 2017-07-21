#ifndef FOR_STMT_H
#define FOR_STMT_H

#include "statement.hpp"
#include "codegen_context.hpp"
#include "assignment.hpp"
#include "expression.hpp"
#include "basic_block.hpp"

class tree_node;

using namespace llvm;
class for_stmt : public statement {
protected:
  assignment  *first_assign, *second_assign;
  expression  *exp;
  basic_block *block;
public:
  for_stmt(tree_node *fa,
           tree_node *exp,
           tree_node *sa,
           tree_node *block,
           YYLTYPE loc);
      
  void print();
  void evaluate();
  Value *emit_ir_code(codegen_context *context);
};

#endif /* FOR_STMT_H */
