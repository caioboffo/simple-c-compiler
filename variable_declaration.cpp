#include "variable_declaration.hpp"

variable_declaration::variable_declaration (int type,
                                            std::list<expression*> *id_list) {
  // list<expression*> is a list<identifier*>
  // deal with scope
  this->type = type;
  this->id_list = id_list;
  
}

void variable_declaration::print() {
  std::list<expression*>::iterator id_iter;
  for (id_iter = id_list->begin(); id_iter != id_list->end();
        id_iter++) {
     std::cout << "variable of type " << type << " and ";
     (*id_iter)->print();
   }  
}

void variable_declaration::evaluate() {

}

