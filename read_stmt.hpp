#ifndef READ_STMT_H
#define READ_STMT_H

#include "statement.hpp"

class read_stmt : public statement {
protected:
  tree_node *var;
public:
  read_stmt(tree_node *v, YYLTYPE loc) {
    this->var = v;
    this->locations = loc;
  }
  void print();
  void evaluate();
};



#endif /* READ_STMT_H */
