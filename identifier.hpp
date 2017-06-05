#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <iostream>
#include <cstring>
#include "tree_node.hpp"
#include "expression.hpp"

class identifier : public expression {
  std::string id;
  int         evaluated_size;
  expression *size;
  expression *initializer;
public:
  identifier(std::string id) : id(id) {}
  identifier(std::string id,
             tree_node *size);
  identifier(tree_node *var, tree_node *init);
  void set_type(int t);
  void print();
  void evaluate();
};


#endif /* IDENTIFIER_H */
