#include "variable_declaration.hpp"
#include "tree_node.hpp"
#include "identifier.hpp"

variable_declaration::variable_declaration (int type,
                                            std::list<tree_node*> *id_list) {
  // list<identifier*> is a list<identifier*>
  // deal with scope
  this->type = type;
  this->id_list = new std::list<identifier*>();

  // set the type of each identifier
  for (auto it = id_list->begin(); it != id_list->end();
        it++) {
    static_cast<identifier*>(*it)->set_type(type);
    this->id_list->push_back(static_cast<identifier*>(*it));
  }
  
}

void variable_declaration::print() {
  
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

void variable_declaration::evaluate() {
  std::cout << "evaluating a variable declaration ...\n";
  for (auto it = id_list->begin(); it != id_list->end();
        it++) {
    (*it)->evaluate();
  }
}

