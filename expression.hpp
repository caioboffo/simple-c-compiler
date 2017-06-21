#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include "tree_node.hpp"
#include "basic_type.hpp"

class expression : public tree_node {
public:
  int value;
  basic_type type;
  expression() {}
  expression(int v) : value(v) {}
  expression(int v, basic_type t) : value(v), type(t) {}
  virtual void set_type(basic_type t);

};

#endif /* EXPRESSION_H */
