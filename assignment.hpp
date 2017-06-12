#ifndef ASSIGMENT_H
#define ASSIGMENT_H

#include <iostream>
#include <string>
#include "statement.hpp"

class expression;
class identifier;
class tree_node;


class assignment : public statement {
protected:
  identifier *id;
  expression *exp;
public:
  assignment(identifier *var, tree_node *exp) {
    this->id = var;
    this->exp = static_cast<expression*>(exp);
  }
  void print();
  void evaluate();
};

#endif /* ASSIGMENT_H */
