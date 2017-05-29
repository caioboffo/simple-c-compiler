#ifndef EQUAL_OPERATION_H
#define EQUAL_OPERATION_H

#include <iostream>
#include "operation.hpp"

class equal_operation : public operation {
public:
  equal_operation(expression *l, expression *r) : operation(l, r) {} 
  void print();
  int evaluate();
};


#endif /* EQUAL_OPERATION_H */
