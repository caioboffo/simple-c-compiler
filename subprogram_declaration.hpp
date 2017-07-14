#ifndef SUBPROGRAM_DECLARATION_H
#define SUBPROGRAM_DECLARATION_H

#include <string>
#include <list>
#include "basic_block.hpp"
#include "symbol.hpp"
#include "symbol_declaration.hpp"
#include "tree_node.hpp"
#include "statement.hpp"

using namespace llvm;

class subprogram_declaration : public statement {
protected:
  symbol                         *name;
  std::list<symbol_declaration*> *param_list;
  basic_block                    *block;
  
public:
  subprogram_declaration(std::string            id,
                         std::list<tree_node*> *parameters,
                         tree_node             *compound_statement,
                         YYLTYPE loc);

  subprogram_declaration(basic_type             t,
                         std::string            id,
                         std::list<tree_node*> *parameters,
                         tree_node             *compound_statement,
                         YYLTYPE loc);

  void print();
  void evaluate();
  Value *emit_ir_code(codegen_context *context);
};

#endif /* SUBPROGRAM_DECLARATION_H */
