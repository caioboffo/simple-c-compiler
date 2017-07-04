#ifndef ASSIGMENT_H
#define ASSIGMENT_H

#include <iostream>
#include <string>
#include "statement.hpp"

class expression;
class symbol;
class tree_node;

class assignment : public statement {
protected:
  symbol *id;
  expression *exp;
public:
  assignment(symbol *var, tree_node *exp, YYLTYPE loc) {
    this->id = var;
    this->exp = static_cast<expression*>(exp);
    this->locations = loc;
  }
  void print();
  void evaluate();
};

#endif /* ASSIGMENT_H */
