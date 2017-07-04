#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <iostream>
#include <string>
#include "locations.hpp"

class tree_node {
public:
  YYLTYPE locations;
  virtual void print() {}
  virtual void evaluate() {}
  tree_node() {}
  tree_node(YYLTYPE loc) : locations(loc) {}
};

#endif /* TREE_NODE_H */
