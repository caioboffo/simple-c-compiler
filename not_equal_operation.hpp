#ifndef NOT_EQUAL_OPERATION_H
#define NOT_EQUAL_OPERATION_H


#include <iostream>
#include "operation.hpp"

class not_equal_operation : public operation {
public:
  not_equal_operation(tree_node *l, tree_node *r, YYLTYPE loc)
    : operation(l, r, loc) {} 
  void print();
  void evaluate();
};


#endif /* NOT_EQUAL_OPERATION_H */
