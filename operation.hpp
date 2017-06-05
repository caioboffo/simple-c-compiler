#ifndef OPERATION_H
#define OPERATION_H

#include "expression.hpp"
#include "tree_node.hpp"

class operation : public expression {
public:
  expression *left;
  expression *right;
  operation() {}
  operation(expression *left, expression *right) : left(left), right(right) {}
  operation(tree_node  *left, tree_node  *right) {
    this->left = static_cast<expression*>(left);
    this->right = static_cast<expression*>(right);
  }
};

#endif /* OPERATION_H */
