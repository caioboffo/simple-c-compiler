#ifndef STATEMENT_H
#define STATEMENT_H

#include "tree_node.hpp"
#include "basic_type.hpp"

class statement : public tree_node {
public:
  basic_type return_type;
};

#endif /* STATEMENT_H */
