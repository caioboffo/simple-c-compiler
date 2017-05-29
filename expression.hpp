#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <cstring>

class expression {
public:
  int value;
  int type;
  expression();
  expression(int v) : value(v) {}
  expression(int v, int t) : value(v), type(t) {}
  virtual void set_type(int t);
  virtual void print() = 0;
  virtual int evaluate() = 0;
};

#endif /* EXPRESSION_H */
