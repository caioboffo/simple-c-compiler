#ifndef BASIC_BLOCK_H
#define BASIC_BLOCK_H

#include <list>
#include "tree_node.hpp"
#include "statement.hpp"

using namespace llvm;

class basic_block : public statement {
protected:
  std::list<tree_node*> *statement_list;
public:
  bool return_stmt;
  basic_block(YYLTYPE loc);
  
  basic_block(std::list<tree_node*> *stmt_list, YYLTYPE loc);
  
  basic_block(std::list<tree_node*> *var_dec_list,
              std::list<tree_node*> *stmt_list,
              YYLTYPE loc);

  void print();
  void evaluate();
  Value *emit_ir_code(codegen_context *context);
};

#endif /* BASIC_BLOCK_H */
