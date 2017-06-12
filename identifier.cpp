#include "identifier.hpp"
#include "string_literal.hpp"
#include "boolean.hpp"
#include "number.hpp"

identifier::identifier(std::string id, tree_node *size) {
  this->id = id;
  this->size = static_cast<expression*>(size);
}

identifier::identifier(tree_node *var, tree_node *init) {
  this->id = static_cast<identifier*>(var)->id;
  if (static_cast<identifier*>(var)->size)
    this->size = static_cast<identifier*>(var)->size;
  initializer = static_cast<expression*>(init);
}

identifier::identifier(tree_node *var, std::list<tree_node*> *init_list) {
  this->id = static_cast<identifier*>(var)->id;
  this->initializer_list = init_list;
}

void identifier::set_type(int t) {
  this->type = t;

  // use this code only when debug_output is enabled
  if (initializer == NULL) {
    switch (type) {
    case 10: {
      initializer = new number(0);
      break;
    }
    case 20: {
      initializer = new boolean(0);
      break;
    }
    case 30: {
      initializer = new string_literal("");
      break;
    }
    default:
      break;
    }
  }
  
}

void identifier::print() {
  std::cout << id << " = ";
  if (initializer)
    initializer->print();
  else
    std::cout << value;
  std::cout << std::endl;
}

void identifier::evaluate() {
  std::cout << "evaluating identifier ...\n" ;
  if (size) {
    std::cout << "eval id size ...\n";
    size->evaluate();
  }
  if (initializer) {
    std::cout <<  "eval init ...\n";
    initializer->evaluate();
  }
  if (initializer_list) {
    std::cout << "eval init_list ...\n";
    for (auto it = initializer_list->begin();
         it != initializer_list->end();
         it ++) {
      // evaluate each one of the literals in the list
      (*it)->evaluate();
    }
  }
}

