#ifndef WHILE_STMT_H
#define WHILE_STMT_H

#include "statement.hpp"
#include "expression.hpp"
#include "basic_block.hpp"

class while_stmt : public statement {
protected:
  expression *exp;
  basic_block *block;
public:
  while_stmt(tree_node* expr,
             tree_node *block,
             YYLTYPE loc) {
    this->exp = static_cast<expression*>(expr);
    this->block = static_cast<basic_block*>(block);
    this->locations = loc;
  }
  void print();
  void evaluate();
};

#endif /* WHILE_STMT_H */
