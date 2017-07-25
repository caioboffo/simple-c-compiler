#include "symbol.hpp"
#include "error_manager.hpp"
#include "string_literal.hpp"
#include "boolean.hpp"
#include "number.hpp"
#include "symbol_table.hpp"
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/InstrTypes.h>

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
    this->string_value = si->value.s_val;
    this->value = si->value.i_val;
    this->array_size = si->value.sz;

    if (this->array_size > 0)
      is_array_type = true;
        
  }

  // symbol is array size must evaluate the expression size
  // into a digit
  if (size) {
    size->evaluate();
    if (size->type != basic_type::INTEGER)
      error_manager::error("array size must be a numeric expression",
                           this->locations);

    if (array_size > 0 && size->value > array_size -1)
      error_manager::error("array indice out of bounds", this->locations);
    
    if (size->value < 0)
      error_manager::error("array size must be positive", this->locations);
    
    if (array_size < 0) {
      symbol_table::update_symbol_value(id,
                                        this->size->value,
                                        this->value,
                                        this->string_value);
    }
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
    symbol_table::update_symbol_value(id,
                                      this->array_size,
                                      this->value,
                                      this->string_value);
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

  if (is_parameter && is_array_type) {
    std::vector<Constant*> idx;
    idx.push_back(ConstantInt::get(getGlobalContext(),
                                   APInt(32, StringRef("0"), 10)));
    idx.push_back(ConstantInt::get(getGlobalContext(),
                                   APInt(32, StringRef("0"), 10)));
          
    return ConstantExpr::getGetElementPtr(
               ArrayType::get(IntegerType::get(getGlobalContext(), 8), 
                              array_size),
               (Constant*) context->find(id),
               idx);
    
  } else if (size) {

    std::vector<Value*> indices;
    indices.push_back(ConstantInt::get(getGlobalContext(),
                                       APInt(64, StringRef("0"), 10)));
    indices.push_back(new SExtInst(this->size->emit_ir_code(context),
                                   IntegerType::get(getGlobalContext(), 64),
                                   "",
                                   context->current_block()));

    GetElementPtrInst *array_elem
      = GetElementPtrInst::Create(
                                  nullptr,
                                  context->find(id),
                                  indices,
                                  Twine(""),
                                  context->current_block());
    
    return new LoadInst(array_elem,
                        "",
                        false,
                        context->current_block());
  } else {
    return new LoadInst(context->find(id),
                        "",
                        false,
                        context->current_block());
  }
}

