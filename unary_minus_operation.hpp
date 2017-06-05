#ifndef UNARY_MINUS_OPERATION_H
#define UNARY_MINUS_OPERATION_H

#include <iostream>
#include "operation.hpp"

class expression;

class unary_minus_operation : public operation {
protected:
  expression *exp;
public:
  unary_minus_operation(tree_node *exp) {
    this->exp = static_cast<expression*>(exp);
  }
  void print();
  void evaluate();
  
};

#endif /* UNARY_MINUS_OPERATION_H */
