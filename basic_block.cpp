#include <iostream>
#include "basic_block.hpp"

basic_block::basic_block(YYLTYPE loc) {
  this->return_stmt = false;
  this->statement_list = new std::list<tree_node*>();
  this->locations = loc;
}

basic_block::basic_block(std::list<tree_node*> *stmt_list, YYLTYPE loc) {
  this->return_stmt = false;
  this->statement_list = stmt_list;
  this->locations = loc;
}

basic_block::basic_block(std::list<tree_node*> *var_dec_list,
                         std::list<tree_node*> *stmt_list,
                         YYLTYPE loc) {

  this->return_stmt = false;
  // add variable declarations at the begining of the list
  this->statement_list = var_dec_list;

  // add other statatement in the list 
  for (auto stmt = stmt_list->begin();
       stmt != stmt_list->end();
       stmt++) {
    this->statement_list->push_back((*stmt));
  }
  this->locations = loc;
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

  #ifdef RETURN_STATUS
  std::cout << "block returns " << to_string(this->return_type) << "\n";
  #endif
  
  if (statement_list->size() > 0) 
    for (auto stmt = statement_list->begin();
         stmt != statement_list->end();
         stmt++) {
      (*stmt)->parent = this;
      (*stmt)->evaluate();
    }
}
