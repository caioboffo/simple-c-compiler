#ifndef TIMES_OPERATION_H
#define TIMES_OPERATION_H

#include <iostream>
#include "operation.hpp"

class times_operation : public operation {
public:
  times_operation(expression *l, expression *r) : operation(l, r) {} 
  void print();
  int evaluate();
};

#endif /* TIMES_OPERATION_H */
