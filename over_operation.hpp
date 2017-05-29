#ifndef OVER_OPERATION_H
#define OVER_OPERATION_H

#include <iostream>
#include "operation.hpp"

class over_operation : public operation {
public:
  over_operation(expression *l, expression *r) : operation(l, r) {} 
  void print();
  int evaluate();
};

#endif /* OVER_OPERATION_H */
