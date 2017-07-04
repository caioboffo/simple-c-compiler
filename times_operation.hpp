#ifndef TIMES_OPERATION_H
#define TIMES_OPERATION_H

#include <iostream>
#include "operation.hpp"

class times_operation : public operation {
public:
  times_operation(tree_node *l, tree_node *r, YYLTYPE loc)
    : operation(l, r, loc) {} 
  void print();
  void evaluate();
};

#endif /* TIMES_OPERATION_H */
