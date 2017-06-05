#ifndef MODULE_OPERATION_H
#define MODULE_OPERATION_H

#include <iostream>
#include "operation.hpp"

class module_operation : public operation {
public:
  module_operation(tree_node *l, tree_node *r) : operation(l, r) {} 
  void print();
  void evaluate();
};


#endif /* MODULE_OPERATION_H */
