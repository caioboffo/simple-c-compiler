#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H

#include <iostream>
#include <list>
#include "statement.hpp"
#include "basic_type.hpp"

class expression;
class symbol;

class symbol_declaration : public statement {
public:
  basic_type type;
  std::list<symbol*> *id_list;
  symbol_declaration(basic_type type,
                     std::list<tree_node*> *id_list,
                     YYLTYPE loc);
  void print();
  void evaluate();
  llvm::Value *emit_ir_code(codegen_context *context);
};


#endif /* VARIABLE_DECLARATION_H */
