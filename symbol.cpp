#include "symbol.hpp"
#include "error_manager.hpp"
#include "string_literal.hpp"
#include "boolean.hpp"
#include "number.hpp"
#include "symbol_table.hpp"
#include <llvm/IR/Instructions.h>

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

  symbol_table::symbol_info *si = symbol_table::lookup(this->id,
                                                       this->locations);
  if (si->type == basic_type::PROCEDURE ||
      si->type == basic_type::FUNCTION ) {
    this->type = si->return_type;
  } else {
    this->type = si->type;
  }

  // symbol is array size must evaluate the expression size
  // into a digit
  if (size) {
    size->evaluate();
    if (size->type != basic_type::INTEGER)
      error_manager::error("array size must be a numeric expression",
                           this->locations);
  }
  
  // symbol is assigned to some value so evaluate its assignment
  if (initializer) {
    if (is_array_type) {
      std::string err
        = "assignment for variable " + this->id
        + " should be of type initializer list";
      error_manager::error(err.c_str(), initializer->locations);
    }
    initializer->evaluate();
    if (this->type != initializer->type) {
      std::string err
        = "assignment for variable " + this->id
        + " should be of type " + to_string(this->type);
      error_manager::error(err.c_str(), initializer->locations);
    }
    this->value = initializer->value;
    this->string_value = initializer->string_value;
  }
  // symbol is an array and this is the list of values assigned to it
  // so evaluate each symbol (literal)
  if (initializer_list) {
    for (auto it = initializer_list->begin();
         it != initializer_list->end();
         it ++) {
      // evaluate each one of the literals in the list
      (*it)->evaluate();
      if (this->type != static_cast<expression*>(*it)->type) {
        std::string err
        = "assignment for variable " + this->id
          + " should be of type " + to_string(this->type);
        error_manager::error(err.c_str(),
                             static_cast<expression*>(*it)->locations);
      }
    }
  }
}

Value *symbol::emit_ir_code(codegen_context* context) {
  return new LoadInst(context->find(id), "", false, context->current_block()); 
}
