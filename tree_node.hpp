#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <iostream>
#include <string>
#include "locations.hpp"

class tree_node {
protected:
  YYLTYPE locations;
  
public:
  virtual void print() {}
  virtual void evaluate() {}
};

#endif /* TREE_NODE_H */
