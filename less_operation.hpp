#ifndef LESS_OPERATION_H
#define LESS_OPERATION_H

#include <iostream>
#include "operation.hpp"

class less_operation : public operation {
public:
  less_operation(tree_node *l, tree_node *r, YYLTYPE loc)
    : operation(l, r, loc) {} 
  void print();
  void evaluate();
};


#endif /* LESS_OPERATION_H */
