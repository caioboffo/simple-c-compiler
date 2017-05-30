#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H

#include <iostream>
#include <list>
#include "statement.hpp"

class identifier;
class expression;

class variable_declaration : public statement {
  int type, evaluated_size;
  std::list<identifier*> *id_list;
  expression *size, *initializer;
public:
  variable_declaration(int type, std::list<identifier*> *id_list);
  void print();
  void evaluate();
};


#endif /* VARIABLE_DECLARATION_H */
