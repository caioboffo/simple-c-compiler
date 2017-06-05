#ifndef OVER_OPERATION_H
#define OVER_OPERATION_H

#include <iostream>
#include "operation.hpp"

class over_operation : public operation {
public:
  over_operation(tree_node *l, tree_node *r) : operation(l, r) {} 
  void print();
  void evaluate();
};

#endif /* OVER_OPERATION_H */
