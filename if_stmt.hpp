#ifndef IF_STMT_H
#define IF_STMT_H

#include "statement.hpp"

class if_stmt : public statement {
protected:
  tree_node *exp;
  tree_node *then_block, *else_block;
public:
  if_stmt(tree_node *exp,
          tree_node *then_block,
          YYLTYPE loc,
          tree_node *else_block = NULL) {
    this->exp = exp;
    this->then_block = then_block;
    this->else_block = else_block;
    this->locations = loc;
  }
    
  void print();
  void evaluate();
};

#endif /* IF_STMT_H */
