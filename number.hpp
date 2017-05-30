#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include "expression.hpp"

class number : public expression {
public:
  number(int v) : expression(v, 10)  {}
  void print();
  void evaluate();
};

#endif /* NUMBER_H */
