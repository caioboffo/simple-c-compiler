#ifndef SUBPROGRAM_DECLARATION_H
#define SUBPROGRAM_DECLARATION_H

#include <string>
#include <list>
#include "basic_type.hpp"
#include "symbol.hpp"
#include "tree_node.hpp"
#include "statement.hpp"

class subprogram_declaration : public statement {
protected:
  basic_type             return_type;
  symbol                *name;
  std::list<tree_node*> *params;
  tree_node             *block;
  
public:
  subprogram_declaration(std::string            id,
                         std::list<tree_node*> *parameters,
                         tree_node             *compound_statement);

  subprogram_declaration(basic_type             t,
                         std::string            id,
                         std::list<tree_node*> *parameters,
                         tree_node             *compound_statement);

  void print();
  void evaluate();
};

#endif /* SUBPROGRAM_DECLARATION_H */