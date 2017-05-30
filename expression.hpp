#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <cstring>
#include "tree_node.hpp"

class expression : public tree_node {
public:
  int value;
  int type;
  expression() {}
  expression(int v) : value(v) {}
  expression(int v, int t) : value(v), type(t) {}
  virtual void set_type(int t);

};

#endif /* EXPRESSION_H */
