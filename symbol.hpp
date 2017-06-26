#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>
#include <string>
#include <list>
#include "tree_node.hpp"
#include "expression.hpp"
#include "basic_type.hpp"

class symbol : public expression {
  std::string id;
  bool        is_array_type;
  expression  *size,
              *initializer;
  
  std::list<tree_node*> *initializer_list; 
public:
  symbol(std::string id) : id(id),
                           size(NULL),
                           initializer(NULL),
                           is_array_type(false) {}

  symbol(std::string id, YYLTYPE loc);
  symbol(std::string id,
         tree_node *size);
  symbol(std::string id,
         tree_node *size,
         YYLTYPE loc);
  symbol(tree_node *var, tree_node *init, YYLTYPE loc);
  symbol(tree_node *var,
         std::list<tree_node*> *init_list,
         YYLTYPE loc);

  void set_type(basic_type t);
  void print();
  void evaluate();
};


#endif /* SYMBOL_H */
