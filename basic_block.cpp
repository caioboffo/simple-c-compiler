#include <iostream>
#include "basic_block.hpp"

basic_block::basic_block() {
  this->statement_list = new std::list<tree_node*>();
}

basic_block::basic_block(std::list<tree_node*> *stmt_list) {
  this->statement_list = stmt_list;
}

basic_block::basic_block(std::list<tree_node*> *var_dec_list,
                         std::list<tree_node*> *stmt_list) {

  // add variable declarations at the begining of the list
  this->statement_list = var_dec_list;

  // add other statatement in the list 
  for (auto stmt = stmt_list->begin();
       stmt != stmt_list->end();
       stmt++) {
    this->statement_list->push_back((*stmt));
  }
}

void basic_block::print() {
  std::cout << "{\n";
  if (statement_list->size() > 0) 
    for (auto stmt = statement_list->begin();
         stmt != statement_list->end();
         stmt++) {
      (*stmt)->print();
      std::cout << "\n";
    }
  std::cout << "}";
}

void basic_block::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a block\n";
  #endif
  
  if (statement_list->size() > 0) 
    for (auto stmt = statement_list->begin();
         stmt != statement_list->end();
         stmt++) {
      (*stmt)->evaluate();
    }
}
