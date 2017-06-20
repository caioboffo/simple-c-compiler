#include "symbol_declaration.hpp"
#include "tree_node.hpp"
#include "symbol.hpp"

symbol_declaration::symbol_declaration (int type,
                                            std::list<tree_node*> *id_list) {
  // list<symbol*> is a list<symbol*>
  // deal with scope
  this->type = type;
  this->id_list = new std::list<symbol*>();

  // set the type of each symbol
  for (auto it = id_list->begin(); it != id_list->end();
        it++) {
    static_cast<symbol*>(*it)->set_type(type);
    this->id_list->push_back(static_cast<symbol*>(*it));
  }
  
}

void symbol_declaration::print() {
  
  for (auto it = id_list->begin(); it != id_list->end();
        it++) {
    switch (type) {
    case 10: {
      std::cout << "int ";
      break;
    }
    case 20: {
      std::cout << "bool ";
      break;
    }
    case 30: {
      std::cout << "string ";
      break;
    }
    default:
      std::cout << "unkown ";
      break;
    }
    (*it)->print();
   }  
}

void symbol_declaration::evaluate() {
  std::cout << "evaluating a variable declaration ...\n";
  for (auto it = id_list->begin(); it != id_list->end();
        it++) {
    (*it)->evaluate();
  }
}

