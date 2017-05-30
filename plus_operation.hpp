#ifndef PLUS_OPERATION_H
#define PLUS_OPERATION_H

#include <iostream>
#include "operation.hpp"

class plus_operation : public operation {
public:
  plus_operation(expression *l, expression *r) : operation(l, r) {} 
  void print();
  void evaluate();
};

#endif /* PLUS_OPERATION_H */
