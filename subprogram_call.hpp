#ifndef SUBPROGRAM_CALL_H
#define SUBPROGRAM_CALL_H

#include <list>
#include <string>
#include "statement.hpp"
#include "expression.hpp"
#include "tree_node.hpp"

class subprogram_call : public statement {
protected:
  tree_node *identifier;
  std::list<tree_node*> *parameters;
  expression *return_value;
public:
  subprogram_call(std::string id,
                  std::list<tree_node*> *param,
                  YYLTYPE loc);
  void print();
  void evaluate();
};

#endif /* SUBPROGRAM_CALL_H */
