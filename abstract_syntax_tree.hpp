#ifndef ABSTRACT_SYNTAX_TREE_H
#define ABSTRACT_SYNTAX_TREE_H

#include <list>
#include "tree_node.hpp"

class abstract_syntax_tree : public tree_node {
  std::list<tree_node*> *nodes;

public:
  abstract_syntax_tree(std::list<tree_node*> *nodelist)
    : nodes(nodelist) {}

  void evaluate();
};

#endif /* ABSTRACT_SYNTAX_TREE_H */
