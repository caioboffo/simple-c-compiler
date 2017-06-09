#ifndef OR_OPERATION_H
#define OR_OPERATION_H

#include <iostream>
#include "operation.hpp"

class or_operation : public operation {
public:
  or_operation(tree_node *l, tree_node *r) : operation(l, r) {} 
  void print();
  void evaluate();
};

#endif /* OR_OPERATION_H */