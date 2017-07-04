#ifndef LESS_OR_EQUAL_OPERATION_H
#define LESS_OR_EQUAL_OPERATION_H

#include <iostream>
#include "operation.hpp"

class less_or_equal_operation : public operation {
public:
  less_or_equal_operation(tree_node *l, tree_node *r, YYLTYPE loc)
    : operation(l, r, loc) {} 
  void print();
  void evaluate();
};


#endif /* LESS_OR_EQUAL_OPERATION_H */
