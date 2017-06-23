#ifndef RETURN_STMT_H
#define RETURN_STMT_H

#include "statement.hpp"

class tree_node;

class return_stmt : public statement {
protected:
  tree_node *return_expression;
public:
  return_stmt() {}
  return_stmt(tree_node *re) : return_expression(re) {}
  void print();
  void evaluate();
};

#endif /* RETURN_STMT_H */
