#ifndef UNARY_NOT_OPERATION_H
#define UNARY_NOT_OPERATION_H

#include <iostream>
#include "operation.hpp"

class expression;

class unary_not_operation : public operation {
protected:
  expression *exp;
public:
  unary_not_operation(tree_node *exp) {
    this->exp = static_cast<expression*>(exp);
  }
  void print();
  void evaluate();

};

#endif /* UNARY_NOT_OPERATION_H */
