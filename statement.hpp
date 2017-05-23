#ifndef STATEMENT_H
#define STATEMENT_H

class statement {
public:
  virtual void print() {}      /* may be override */
  virtual void evaluate() = 0; /* must be override */
};

#endif /* STATEMENT_H */
