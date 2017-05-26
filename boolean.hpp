#ifndef BOOLEAN_H
#define BOOLEAN_H

#include <iostream>
#include "expression.hpp"

class boolean : public expression {
public:
  boolean(int v) : expression(v) {}
  void print();
  int evaluate();
};

#endif /* BOOLEAN_H */
