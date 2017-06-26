#include "symbol.hpp"
#include "string_literal.hpp"
#include "boolean.hpp"
#include "number.hpp"

symbol::symbol(std::string id, YYLTYPE loc) {
  this->id = id;
  this->locations = loc;
  this->is_array_type = false;
}

symbol::symbol(std::string id, tree_node *size) {
  this->id = id;
  this->size = static_cast<expression*>(size);
  this->is_array_type = true;
}

symbol::symbol(std::string id, tree_node *size, YYLTYPE loc) {
  this->id = id;
  this->size = static_cast<expression*>(size);
  this->is_array_type = true;
  this->locations = loc;
}

symbol::symbol(tree_node *var, tree_node *init, YYLTYPE loc) {
  this->id = static_cast<symbol*>(var)->id;
  this->is_array_type = static_cast<symbol*>(var)->is_array_type;
  
  if (static_cast<symbol*>(var)->size)
    this->size = static_cast<symbol*>(var)->size;
  
  initializer = static_cast<expression*>(init);
  this->locations = loc;
}

symbol::symbol(tree_node *var,
               std::list<tree_node*> *init_list,
               YYLTYPE loc) {
  this->id = static_cast<symbol*>(var)->id;
  this->is_array_type = static_cast<symbol*>(var)->is_array_type;
  this->size = static_cast<symbol*>(var)->size;
  this->initializer_list = init_list;
  this->locations = loc;
}

void symbol::set_type(basic_type t) {
  this->type = t;

  #ifdef SOURCE_OUTPUT
  // use this code only when debug_output is enabled
  if (initializer == NULL) {
    switch (type) {
    case basic_type::INTEGER: {
      initializer = new number(0);
      break;
    }
    case basic_type::BOOLEAN: {
      initializer = new boolean(0);
      break;
    }
    case basic_type::STRING: {
      initializer = new string_literal("");
      break;
    }
    default:
      break;
    }
  }
  #endif
}

void symbol::print() {
  std::cout << id;
  if (is_array_type) {
    std::cout << "[";
    size->print();
    std::cout << "]";

    if (initializer_list) {
      std::cout << " = {";
      int index = 1;
      for (auto it=initializer_list->begin();
           it != initializer_list->end();
           it++, index++) {
        (*it)->print();
        if (index != initializer_list->size())
          std::cout << ", ";
      }
    
      std::cout << "}";
    }
  } else {
    if (initializer) {
      std::cout << " = ";
      initializer->print();
    } 
  }
}

void symbol::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating symbol " << id << "\n" ;
  #endif
  
  // symbol is array size must evaluate the expression size
  // into a digit
  if (size) {
    size->evaluate();
    if (size->type != basic_type::INTEGER)
      error("array size must be a numeric expression");
  }
  
  // symbol is assigned to some value so evaluate its assignment
  if (initializer) {
    initializer->evaluate();
  }
  // symbol is an array and this is the list of values assigned to it
  // so evaluate each symbol (literal)
  if (initializer_list) {
    for (auto it = initializer_list->begin();
         it != initializer_list->end();
         it ++) {
      // evaluate each one of the literals in the list
      (*it)->evaluate();
    }
  }
}

