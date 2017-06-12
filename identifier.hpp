#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <iostream>
#include <string>
#include <list>
#include "tree_node.hpp"
#include "expression.hpp"

class identifier : public expression {
  std::string id;
  int         evaluated_size;
  expression *size, *initializer;
  std::list<tree_node*> *initializer_list; 
public:
  identifier(std::string id) : id(id), size(NULL), initializer(NULL) {}
  identifier(std::string id,
             tree_node *size);
  identifier(tree_node *var, tree_node *init);
  identifier(tree_node *var, std::list<tree_node*> *init_list);
  void set_type(int t);
  void print();
  void evaluate();
};


#endif /* IDENTIFIER_H */
