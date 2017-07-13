#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include "expression.hpp"

class number : public expression {
public:
  number(int v) : expression(v, basic_type::INTEGER)  {}
  number(int v, YYLTYPE loc);
  void print();
  void evaluate();
  llvm::Value *emit_ir_code();
};

#endif /* NUMBER_H */
