#ifndef EQUAL_OPERATION_H
#define EQUAL_OPERATION_H

#include <iostream>
#include "operation.hpp"

class equal_operation : public operation {
public:
  equal_operation(tree_node *l, tree_node *r) : operation(l, r) {} 
  void print();
  void evaluate();
};


#endif /* EQUAL_OPERATION_H */
