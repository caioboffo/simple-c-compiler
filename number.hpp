#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include "expression.hpp"

using namespace llvm;

class number : public expression {
public:
  number(int v) : expression(v, basic_type::INTEGER)  {}
  number(int v, YYLTYPE loc);
  void print();
  void evaluate();
  Value *emit_ir_code(codegen_context *context);
};

#endif /* NUMBER_H */
