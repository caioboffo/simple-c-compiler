#ifndef FOR_STMT_H
#define FOR_STMT_H

#include "statement.hpp"

class tree_node;

class for_stmt : public statement {
protected:
  tree_node *first_assign, *exp, *second_assign, *block;
public:
  for_stmt(tree_node *fa,
           tree_node *exp,
           tree_node *sa,
           tree_node *block,
           YYLTYPE loc) {
    first_assign = fa;
    exp = exp;
    second_assign = sa;
    block = block;
    this->locations = loc;
  }
      
  void print();
  void evaluate();
};

#endif /* FOR_STMT_H */
