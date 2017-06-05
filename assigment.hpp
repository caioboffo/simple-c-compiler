#ifndef ASSIGMENT_H
#define ASSIGMENT_H

#include <iostream>
#include <cstring>
#include "statement.hpp"

class expression;
class identifier;
class tree_node;


class assigment : public statement {
protected:
  identifier *id;
  expression *exp;
public:
  assigment(identifier *var, tree_node *exp) {
    this->id = var;
    this->exp = static_cast<expression*>(exp);
  }
  void print();
  void evaluate();
};

#endif /* ASSIGMENT_H */
