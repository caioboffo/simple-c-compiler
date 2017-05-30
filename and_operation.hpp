#ifndef AND_OPERATION_H
#define AND_OPERATION_H

#include <iostream>
#include "operation.hpp"

class and_operation : public operation {
public:
  and_operation(expression *l, expression *r) : operation(l, r) {} 
  void print();
  void evaluate();
};

#endif /* AND_OPERATION_H */
