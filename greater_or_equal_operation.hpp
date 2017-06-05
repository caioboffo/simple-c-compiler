#ifndef GREATER_OR_EQUAL_OPERATION_H
#define GREATER_OR_EQUAL_OPERATION_H

#include <iostream>
#include "operation.hpp"

class greater_or_equal_operation : public operation {
public:
  greater_or_equal_operation(tree_node *l, tree_node *r) : operation(l, r) {} 
  void print();
  void evaluate();
};

#endif /* GREATER_OR_EQUAL_OPERATION_H */
