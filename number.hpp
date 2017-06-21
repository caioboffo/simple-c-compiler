#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include "expression.hpp"
#include "basic_type.hpp"

class number : public expression {
public:
  number(int v) : expression(v, basic_type::INTEGER)  {}
  void print();
  void evaluate();
};

#endif /* NUMBER_H */
