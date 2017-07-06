#ifndef RETURN_STMT_H
#define RETURN_STMT_H

#include "statement.hpp"

class tree_node;

class return_stmt : public statement {
protected:
  expression *return_expression;
public:
  return_stmt(YYLTYPE loc) {
    this->locations = loc;
  }
  return_stmt(tree_node *re, YYLTYPE loc) {
    return_expression = static_cast<expression*>(re);
    this->locations = loc;
  }
    
  void print();
  void evaluate();
};

#endif /* RETURN_STMT_H */
