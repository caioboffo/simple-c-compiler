#ifndef BOOLEAN_H
#define BOOLEAN_H

#include <iostream>
#include "expression.hpp"
#include "basic_type.hpp"

class boolean : public expression {
public:
  boolean(int v) : expression(v, basic_type::BOOLEAN) {}
  void print();
  void evaluate();
};

#endif /* BOOLEAN_H */
