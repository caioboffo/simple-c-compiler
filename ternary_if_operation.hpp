#ifndef TERNARY_IF_OPERATION_H
#define TERNARY_IF_OPERATION_H

#include <iostream>
#include "operation.hpp"

class expression;

class ternary_if_operation : public operation {
protected:
  expression *condition, *then_branch, *else_branch;

public:
  ternary_if_operation(expression *c,
                       expression *t,
                       expression *e) : condition(c), then_branch(t),
                                        else_branch(e) {}
  void print();
  int evaluate();
  
};

#endif /* TERNARY_IF_OPERATION_H */
