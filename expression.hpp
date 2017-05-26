#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <cstring>

class expression {
public:
  int value;
  expression();
  expression(int v) : value(v) {}
  virtual void print() = 0;
  virtual int evaluate() = 0;
};

#endif /* EXPRESSION_H */
