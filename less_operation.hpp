#ifndef LESS_OPERATION_H
#define LESS_OPERATION_H

#include <iostream>
#include "operation.hpp"

class less_operation : public operation {
public:
  less_operation(expression *l, expression *r) : operation(l, r) {} 
  void print();
  void evaluate();
};


#endif /* LESS_OPERATION_H */
