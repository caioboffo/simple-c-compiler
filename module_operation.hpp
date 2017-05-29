#ifndef MODULE_OPERATION_H
#define MODULE_OPERATION_H

#include <iostream>
#include "operation.hpp"

class module_operation : public operation {
public:
  module_operation(expression *l, expression *r) : operation(l, r) {} 
  void print();
  int evaluate();
};


#endif /* MODULE_OPERATION_H */
