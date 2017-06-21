#include "symbol.hpp"
#include "string_literal.hpp"
#include "boolean.hpp"
#include "number.hpp"

symbol::symbol(std::string id, tree_node *size) {
  this->id = id;
  this->size = static_cast<expression*>(size);
  this->is_array_type = true;
}

symbol::symbol(tree_node *var, tree_node *init) {
  this->id = static_cast<symbol*>(var)->id;
  this->is_array_type = static_cast<symbol*>(var)->is_array_type;
  
  if (static_cast<symbol*>(var)->size)
    this->size = static_cast<symbol*>(var)->size;
  
  initializer = static_cast<expression*>(init);
}

symbol::symbol(tree_node *var, std::list<tree_node*> *init_list) {
  this->id = static_cast<symbol*>(var)->id;
  this->is_array_type = static_cast<symbol*>(var)->is_array_type;

  this->initializer_list = init_list;
}

void symbol::set_type(basic_type t) {
  this->type = t;

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
  
}

void symbol::print() {
  std::cout << id << " = ";
  if (initializer)
    initializer->print();
  else
    std::cout << value;
  std::cout << std::endl;
}

void symbol::evaluate() {
  std::cout << "evaluating symbol ...\n" ;
  // symbol is array size must evaluate the expression size
  // into a digit
  if (size) {
    std::cout << "eval id size ...\n";
    size->evaluate();
  }
  // symbol is assigned to some value so evaluate its assignment
  if (initializer) {
    std::cout <<  "eval init ...\n";
    initializer->evaluate();
  }
  // symbol is an array and this is the list of values assigned to it
  // so evaluate each symbol (literal)
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

