#ifndef GREATER_OPERATION_H
#define GREATER_OPERATION_H

#include <iostream>
#include "operation.hpp"

class greater_operation : public operation {
public:
  greater_operation(tree_node *l, tree_node *r) : operation(l, r) {} 
  void print();
  void evaluate();
};


#endif /* GREATER_OPERATION_H */
