#ifndef BREAK_STMT_H
#define BREAK_STMT_H

#include "statement.hpp"
#include "codegen_context.hpp"

using namespace llvm;
class break_stmt : public statement {
public:
  break_stmt(YYLTYPE loc) {
    this->locations = loc;
  }
  void print();
  void evaluate();
  Value *emit_ir_code(codegen_context *context);
};
  

#endif /* BREAK_STMT_H */
