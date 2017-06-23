#ifndef IF_STMT_H
#define IF_STMT_H

#include "statement.hpp"

class if_stmt : public statement {
protected:
  tree_node *exp;
  tree_node *true_block, *else_block;
public:
  if_stmt(tree_node *exp, tree_node *true_block, tree_node *else_block = NULL)
    : exp(exp), true_block(true_block), else_block(else_block) {}
  void print();
  void evaluate();
};

#endif /* IF_STMT_H */
