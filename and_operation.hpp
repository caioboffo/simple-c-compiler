#ifndef AND_OPERATION_H
#define AND_OPERATION_H

#include <iostream>
#include "operation.hpp"

class and_operation : public operation {
public:
  and_operation(tree_node *l, tree_node *r, YYLTYPE loc)
    : operation(l, r, loc) {} 
  void print();
  void evaluate();
};

#endif /* AND_OPERATION_H */
