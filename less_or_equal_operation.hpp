#ifndef LESS_OR_EQUAL_OPERATION_H
#define LESS_OR_EQUAL_OPERATION_H

#include <iostream>
#include "operation.hpp"

class less_or_equal_operation : public operation {
public:
  less_or_equal_operation(expression *l, expression *r) : operation(l, r) {} 
  void print();
  int evaluate();
};


#endif /* LESS_OR_EQUAL_OPERATION_H */
