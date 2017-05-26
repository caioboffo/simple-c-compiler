#ifndef ASSIGMENT_H
#define ASSIGMENT_H

#include <iostream>
#include <cstring>
#include "statement.hpp"

class expression;

class assigment : public statement {
protected:
  std::string id;
  expression *exp;
public:
  assigment(std::string name, expression *exp) : id(name), exp(exp) {}
  void print();
  void evaluate();
};

#endif /* ASSIGMENT_H */
