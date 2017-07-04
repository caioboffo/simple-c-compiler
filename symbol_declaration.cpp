#include "symbol_declaration.hpp"
#include "tree_node.hpp"
#include "symbol.hpp"
#include "symbol_table.hpp"

symbol_declaration::symbol_declaration (basic_type type,
                                        std::list<tree_node*> *id_list,
                                        YYLTYPE loc) {
  // list<symbol*> is a list<symbol*>
  // deal with scope
  this->type = type;
  this->id_list = new std::list<symbol*>();
  this->locations = loc;

  // set the type of each symbol
  for (auto it = id_list->begin(); it != id_list->end();
       it++) {
    static_cast<symbol*>(*it)->set_type(type);
    this->id_list->push_back(static_cast<symbol*>(*it));
  }
}

void symbol_declaration::print() {

  int index = 1;
  for (auto it = id_list->begin(); it != id_list->end();
       it++, index++) {
    switch (type) {
    case basic_type::INTEGER : {
      std::cout << "int ";
      break;
    }
    case basic_type::BOOLEAN : {
      std::cout << "bool ";
      break;
    }
    case basic_type::STRING : {
      std::cout << "string ";
      break;
    }
    default:
      std::cout << "unkown ";
      break;
    }
    (*it)->print();
    if (index != id_list->size())
      std::cout << ", ";
  }  
}

void symbol_declaration::evaluate() {

  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a symbol declaration\n";
  #endif

  for (auto it = this->id_list->begin(); it != this->id_list->end();
       it++) {

    if ((*it)->type == basic_type::STRING)
      symbol_table::insert((*it)->id,
                           (*it)->type,
                           (*it)->string_value,
                           this->locations);
    else
      symbol_table::insert((*it)->id,
                           (*it)->type,
                           (*it)->value,
                           this->locations);

    (*it)->evaluate();
    
  }

}

