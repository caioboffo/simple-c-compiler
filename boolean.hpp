#ifndef BOOLEAN_H
#define BOOLEAN_H

#include <iostream>
#include "expression.hpp"
//#include "basic_type.hpp"

class boolean : public expression {
public:
  boolean(int v) : expression(v, basic_type::BOOLEAN) {}
  boolean(int v, YYLTYPE loc);
  void print();
  void evaluate();
  llvm::Value *emit_ir_code();
};

#endif /* BOOLEAN_H */
