#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/ADT/Twine.h>

#include "symbol.hpp"
#include "error_manager.hpp"
#include "string_literal.hpp"
#include "boolean.hpp"
#include "number.hpp"
#include "symbol_table.hpp"

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

Value *symbol::emit_ir_code(codegen_context *context) {

  symbol_table::symbol_info *si = symbol_table::lookup(this->id,
                                                       this->locations);
  if (symbol_table::current_scope_num == 0) {
    GlobalVariable *var;
    if (si->type == basic_type::STRING) {
      if (this->initializer) {
        ArrayType* _array
          = ArrayType::get(
                  IntegerType::get(getGlobalContext(), 8),
                  this->initializer->string_value.size()+1);
        var
          = new GlobalVariable(
                *context->module,
                _array,
                false,
                GlobalValue::CommonLinkage,
                0,
                Twine(this->id));

        var->setAlignment(1);
        
        var->setInitializer(static_cast<Constant*>(this->initializer->emit_ir_code(context)));
        
      } else  {
        var =
          new GlobalVariable(
                *context->module,
                PointerType::get(IntegerType::get(
                                         getGlobalContext(), 8), 0),
                false,
                GlobalValue::CommonLinkage,
                0,
                Twine(this->id));
        var->setAlignment(8);
        
      }
    } else { // is not a string
      if (is_array_type) {
        ArrayType* _array
          = ArrayType::get(
              IntegerType::get(getGlobalContext(), 32),
              this->size->value);
        var = new GlobalVariable(
                *context->module,
                _array,
                false,
                GlobalValue::CommonLinkage,
                0,
                Twine(this->id));

        if (initializer_list) {
          var->setAlignment(4);
          std::vector<Constant*> const_array_elems;
          for (auto item = initializer_list->begin();
               item != initializer_list->end();
               item++) {

            const_array_elems.push_back(ConstantInt::get(
                  getGlobalContext(),
                  APInt(32,
                              StringRef(std::to_string(
                                static_cast<expression*>(*item)->value
                                                             )),
                              10)));
          }

          Constant* const_array
            = ConstantArray::get(_array,
                                       const_array_elems);

          var->setInitializer(const_array);
          

        }
        else  {
          var->setAlignment(16);
        }
        
      } else {
        
        var = new GlobalVariable(
          *context->module,
          IntegerType::get(getGlobalContext(), 32),
          false,
          GlobalValue::CommonLinkage,
          0,
          Twine(this->id));
      
        if (this->initializer)
          var->setInitializer(
            static_cast<Constant*>(this->initializer->emit_ir_code(context)));
        
        var->setAlignment(4);

      }
      
      return var;
      
    }
  } else {}

  return NULL;
  
}
