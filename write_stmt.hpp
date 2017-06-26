#ifndef WRITE_STMT_H
#define WRITE_STMT_H

#include <list>
#include "statement.hpp"

class write_stmt : public statement {
protected:
  std::list<tree_node*> *expressions;

public:
  write_stmt(std::list<tree_node*> *exps, YYLTYPE loc) {
    this->expressions = exps;
    this->locations = loc;
  }
  void print();
  void evaluate();
};

#endif /* WRITE_STMT_H */
