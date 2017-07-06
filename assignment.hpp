#ifndef ASSIGMENT_H
#define ASSIGMENT_H

#include <iostream>
#include <string>
#include "statement.hpp"

class expression;
class symbol;
class tree_node;

class assignment : public expression {
protected:
  symbol *id;
  expression *rhs;
public:
  assignment(symbol *var, tree_node *exp, YYLTYPE loc) {
    this->id = var;
    this->rhs = static_cast<expression*>(exp);
    this->locations = loc;
  }
  void print();
  void evaluate();
};

#endif /* ASSIGMENT_H */
