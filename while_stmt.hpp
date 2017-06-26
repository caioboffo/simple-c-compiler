#ifndef WHILE_STMT_H
#define WHILE_STMT_H

#include "statement.hpp"

class tree_node;

class while_stmt : public statement {
protected:
  tree_node *exp, *block;
public:
  while_stmt(tree_node* expr,
             tree_node *block,
             YYLTYPE loc) {
    this->exp = expr;
    this->block = block;
    this->locations = loc;
  }
  void print();
  void evaluate();
};

#endif /* WHILE_STMT_H */
