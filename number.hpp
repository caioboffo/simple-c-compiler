#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include "expression.hpp"

class number : public expression {
public:
  number(int v) : expression(v) {}
  void print();
  int evaluate();
};

#endif /* NUMBER_H */
