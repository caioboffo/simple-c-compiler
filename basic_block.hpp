#ifndef BASIC_BLOCK_H
#define BASIC_BLOCK_H

#include <list>
#include "tree_node.hpp"
#include "statement.hpp"

class basic_block : public statement {
protected:
  std::list<tree_node*> *statement_list;
  
public:
  basic_block();
  
  basic_block(std::list<tree_node*> *stmt_list);
  
  basic_block(std::list<tree_node*> *var_dec_list,
              std::list<tree_node*> *stmt_list);

  void print();
  void evaluate();
};

#endif /* BASIC_BLOCK_H */
