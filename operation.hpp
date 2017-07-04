#ifndef OPERATION_H
#define OPERATION_H

#include "expression.hpp"
#include "tree_node.hpp"

class operation : public expression {
public:
  expression *left;
  expression *right;
  operation() {}
  operation(expression *left, expression *right, YYLTYPE loc)
    : left(left), right(right), expression(loc) {}
  operation(tree_node  *left, tree_node  *right, YYLTYPE loc) {
    this->left = static_cast<expression*>(left);
    this->right = static_cast<expression*>(right);
    this->locations = loc;
  }
};

#endif /* OPERATION_H */
