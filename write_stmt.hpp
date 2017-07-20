#ifndef WRITE_STMT_H
#define WRITE_STMT_H

#include <list>
#include "statement.hpp"
#include "expression.hpp"
#include "codegen_context.hpp"

using namespace llvm;

class write_stmt : public statement {
protected:
  std::list<expression*> *expressions;

public:
  write_stmt(std::list<tree_node*> *exps, YYLTYPE loc) {
    expressions = new std::list<expression*>();
    for (auto e = exps->begin();
         e != exps->end();
         e++) {
      expressions->push_back(static_cast<expression*>(*e));
    }
    
    this->locations = loc;
  }
  void print();
  void evaluate();
  Value *emit_ir_code(codegen_context *context);
};

#endif /* WRITE_STMT_H */
