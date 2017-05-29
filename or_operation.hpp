#ifndef OR_OPERATION_H
#define OR_OPERATION_H

#include <iostream>
#include "operation.hpp"

class or_operation : public operation {
public:
  or_operation(expression *l, expression *r) : operation(l, r) {} 
  void print();
  int evaluate();
};

#endif /* OR_OPERATION_H */
