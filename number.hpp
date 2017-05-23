#ifndef NUMBER_H
#define NUMBER_H

#include "expression.hpp"

class number : public expression {
public:
  number(int v) : value(v);
  void print();
  int evaluate();
};

#endif /* NUMBER_H */
