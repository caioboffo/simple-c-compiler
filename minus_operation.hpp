#ifndef MINUS_OPERATION_H
#define MINUS_OPERATION_H

#include <iostream>
#include "operation.hpp"

class minus_operation : public operation {
public:
  minus_operation(expression *l, expression *r) : operation(l, r) {} 
  void print();
  void evaluate();
};


#endif /* MINUS_OPERATION_H */
