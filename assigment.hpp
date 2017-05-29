#ifndef ASSIGMENT_H
#define ASSIGMENT_H

#include <iostream>
#include <cstring>
#include "statement.hpp"

class expression;
class identifier;

class assigment : public statement {
protected:
  identifier *id;
  expression *exp;
public:
  assigment(identifier *var, expression *exp) : id(var), exp(exp) {}
  void print();
  void evaluate();
};

#endif /* ASSIGMENT_H */
