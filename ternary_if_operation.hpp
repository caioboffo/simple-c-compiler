#ifndef TERNARY_IF_OPERATION_H
#define TERNARY_IF_OPERATION_H

#include <iostream>
#include "operation.hpp"

class expression;

class ternary_if_operation : public operation {
protected:
  expression *condition, *then_branch, *else_branch;

public:
  ternary_if_operation(tree_node *c,
                       tree_node *t,
                       tree_node *e,
                       YYLTYPE    loc) {
    condition = static_cast<expression*>(c);
    then_branch = static_cast<expression*>(t);
    else_branch = static_cast<expression*>(e);
    this->locations = loc;
  }
  
  void print();
  void evaluate();
  
};

#endif /* TERNARY_IF_OPERATION_H */
