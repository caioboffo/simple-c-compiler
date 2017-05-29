#ifndef GREATER_OPERATION_H
#define GREATER_OPERATION_H

#include <iostream>
#include "operation.hpp"

class greater_operation : public operation {
public:
  greater_operation(expression *l, expression *r) : operation(l, r) {} 
  void print();
  int evaluate();
};


#endif /* GREATER_OPERATION_H */
