#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H

#include <iostream>
#include <list>
#include "statement.hpp"

class expression;
class symbol;

class variable_declaration : public statement {
  int type;
  std::list<symbol*> *id_list;
public:
  variable_declaration(int type, std::list<tree_node*> *id_list);
  void print();
  void evaluate();
};


#endif /* VARIABLE_DECLARATION_H */
