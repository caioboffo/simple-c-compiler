#ifndef OPERATION_H
#define OPERATION_H

#include "expression.hpp"

class operation : public expression {
public:
  expression *left;
  expression *right;
  operation(expression *left, expression *right) : left(left), right(right) {}
};

#endif /* OPERATION_H */
