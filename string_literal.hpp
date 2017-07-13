#ifndef STRING_LITERAL_H
#define STRING_LITERAL_H

#include <iostream>
#include <string>
#include "expression.hpp"

class string_literal : public expression {
public:
  string_literal(std::string str);
  string_literal(std::string str, YYLTYPE loc);
  void print();
  void evaluate();
  llvm::Value *emit_ir_code();
};

#endif /* STRING_LITERAL_H */
