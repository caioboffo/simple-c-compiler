#include "variable_declaration.hpp"
#include "identifier.hpp"

variable_declaration::variable_declaration (int type,
                                            std::list<identifier*> *id_list) {
  // list<identifier*> is a list<identifier*>
  // deal with scope
  this->type = type;
  this->id_list = id_list;
  std::list<identifier*>::iterator id_iter;
  for (id_iter = id_list->begin(); id_iter != id_list->end();
        id_iter++) {
    (*id_iter)->set_type(type);
  }
  
}

void variable_declaration::print() {
  std::list<identifier*>::iterator id_iter;
  for (id_iter = id_list->begin(); id_iter != id_list->end();
        id_iter++) {
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
    (*id_iter)->print();
   }  
}

void variable_declaration::evaluate() {
  std::cout << "evaluating a variable declaration ...\n";
    std::list<identifier*>::iterator id_iter;
  for (id_iter = id_list->begin(); id_iter != id_list->end();
        id_iter++) {
    (*id_iter)->evaluate();
  }
}

