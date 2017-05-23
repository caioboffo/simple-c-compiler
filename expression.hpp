#ifndef EXPRESSION_H
#define EXPRESSION_H

class expression {
public:
  int value;
  virtual void print() = 0;
  virtual int evaluate() = 0;
};

#endif /* EXPRESSION_H */
