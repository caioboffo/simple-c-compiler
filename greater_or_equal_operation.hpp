#ifndef GREATER_OR_EQUAL_OPERATION_H
#define GREATER_OR_EQUAL_OPERATION_H

#include <iostream>
#include "operation.hpp"

class greater_or_equal_operation : public operation {
public:
  greater_or_equal_operation(expression *l, expression *r) : operation(l, r) {} 
  void print();
  int evaluate();
};

#endif /* GREATER_OR_EQUAL_OPERATION_H */
