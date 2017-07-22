#ifndef SUBPROGRAM_CALL_H
#define SUBPROGRAM_CALL_H

#include <list>
#include <string>
#include "expression.hpp"
#include "tree_node.hpp"
#include "codegen_context.hpp"

class symbol;

using namespace llvm;
class subprogram_call : public expression {
protected:
  symbol *identifier;
  std::list<tree_node*> *parameters;
  expression *return_value;
public:
  subprogram_call(std::string id,
                  std::list<tree_node*> *param,
                  YYLTYPE loc);
  void print();
  void evaluate();
  Value *emit_ir_code(codegen_context *context);
};

#endif /* SUBPROGRAM_CALL_H */
