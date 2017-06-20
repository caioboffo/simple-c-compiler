#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>
#include <string>
#include <list>
#include "tree_node.hpp"
#include "expression.hpp"

class symbol : public expression {
  std::string id;
  int         evaluated_size;
  expression *size, *initializer;
  std::list<tree_node*> *initializer_list; 
public:
  symbol(std::string id) : id(id), size(NULL), initializer(NULL) {}
  symbol(std::string id,
             tree_node *size);
  symbol(tree_node *var, tree_node *init);
  symbol(tree_node *var, std::list<tree_node*> *init_list);
  void set_type(int t);
  void print();
  void evaluate();
};


#endif /* SYMBOL_H */
