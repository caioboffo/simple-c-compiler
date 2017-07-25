#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/ADT/Twine.h>

#include "symbol_declaration.hpp"
#include "tree_node.hpp"
#include "symbol.hpp"
#include "symbol_table.hpp"

symbol_declaration::symbol_declaration (basic_type type,
                                        std::list<tree_node*> *id_list,
                                        YYLTYPE loc) {
  // list<symbol*> is a list<symbol*>
  // deal with scope
  this->type = type;
  this->id_list = new std::list<symbol*>();
  this->locations = loc;

  // set the type of each symbol
  for (auto it = id_list->begin(); it != id_list->end();
       it++) {
    static_cast<symbol*>(*it)->set_type(type);
    this->id_list->push_back(static_cast<symbol*>(*it));
  }
}

void symbol_declaration::print() {

  int index = 1;
  for (auto it = id_list->begin(); it != id_list->end();
       it++, index++) {
    switch (type) {
    case basic_type::INTEGER : {
      std::cout << "int ";
      break;
    }
    case basic_type::BOOLEAN : {
      std::cout << "bool ";
      break;
    }
    case basic_type::STRING : {
      std::cout << "string ";
      break;
    }
    default:
      std::cout << "unkown ";
      break;
    }
    (*it)->print();
    if (index != id_list->size())
      std::cout << ", ";
  }  
}

void symbol_declaration::evaluate() {

  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a symbol declaration\n";
  #endif

  for (auto it = this->id_list->begin(); it != this->id_list->end();
       it++) {


    if ((*it)->type == basic_type::STRING)
      symbol_table::insert((*it)->id,
                           (*it)->type,
                           (*it)->string_value,
                           this->locations);
    else
      symbol_table::insert((*it)->id,
                           (*it)->type,
                           (*it)->value,
                           this->locations);
    (*it)->evaluate();
    
  }
}

Value *symbol_declaration::emit_ir_code(codegen_context *context) {

  Value *var;
  GlobalVariable *global;
  AllocaInst *local;
  StoreInst *store;
  Type *type;
  Constant *init;

  for (auto it = this->id_list->begin();
       it != this->id_list->end();
       it++) {
    
    // Global Variable declaration
    if (symbol_table::current_scope_num == 0) {
      switch ((*it)->type) {
      case basic_type::STRING: {
        type = PointerType::get(IntegerType::get(getGlobalContext(), 8), 0);
        init = ConstantPointerNull::get((PointerType*) type);
        if ((*it)->initializer) {
          init = (Constant*) (*it)->initializer->emit_ir_code(context);
        } 
        break;
      }
      case basic_type::INTEGER: {
        type = IntegerType::get(getGlobalContext(), 32);
        init = ConstantInt::get(getGlobalContext(), APInt(32, 0));

        if ((*it)->is_array_type) {
          type = ArrayType::get(IntegerType::get(getGlobalContext(), 32),
                                  (*it)->size->value);
          init = ConstantAggregateZero::get(type);

          if ((*it)->initializer_list) {
            std::vector<Constant*> const_array;
            for (auto item = (*it)->initializer_list->begin();
                 item != (*it)->initializer_list->end();
                 item++) {

              const_array.push_back(ConstantInt::get(
                                      getGlobalContext(),
                                      APInt(32,
                                        StringRef(std::to_string(
                                        static_cast<expression*>(*item)->value)),
                                         10)));
            }
            init = ConstantArray::get((ArrayType*) type, const_array);
          }
        }

        if ((*it)->initializer) {
          init = (Constant*) (*it)->initializer->emit_ir_code(context);
        }
        
        break;
      }

      case basic_type::BOOLEAN: {
        type = IntegerType::get(getGlobalContext(), 1);
        init = ConstantInt::get(getGlobalContext(), APInt(1, 0));

        if ((*it)->is_array_type) {
          type = ArrayType::get(IntegerType::get(getGlobalContext(),
                                                 1),
                                (*it)->size->value);
          init = ConstantAggregateZero::get(type);
          
          if ((*it)->initializer_list) {
            std::vector<Constant*> const_array;
            for (auto item = (*it)->initializer_list->begin();
                 item != (*it)->initializer_list->end();
                 item++) {

              const_array.push_back(ConstantInt::get(
                                      getGlobalContext(),
                                      APInt(1,
                                        StringRef(std::to_string(
                                        static_cast<expression*>(*item)->value)),
                                         10)));
            }
            init = ConstantArray::get((ArrayType*) type, const_array);
          }
        }

        if ((*it)->initializer) {
          init = (Constant*) (*it)->initializer->emit_ir_code(context);
        }
        break;
      }

      default:
        break;
      }

      global = new GlobalVariable(*context->module,
                                  type,
                                  false,
                                  GlobalValue::ExternalLinkage,
                                  0,
                                  Twine((*it)->id));
      global->setInitializer(init);
      context->globals[(*it)->id] = global;
      var = global;
    }
    // Local Variable declaration
    else {
      switch ((*it)->type) {
      case basic_type::STRING: {
        type = Type::getInt8PtrTy(getGlobalContext(), 0);
        break;
      }
      case basic_type::INTEGER: {
        type = Type::getInt32Ty(getGlobalContext());
        if ((*it)->is_array_type) {
          type = ArrayType::get(IntegerType::get(getGlobalContext(), 32),
                                  (*it)->size->value);
          init = ConstantAggregateZero::get(type);
          if ((*it)->initializer_list) {
            std::vector<Constant*> const_array;
            for (auto item = (*it)->initializer_list->begin();
                 item != (*it)->initializer_list->end();
                 item++) {

              const_array.push_back(ConstantInt::get(
                                      getGlobalContext(),
                                      APInt(32,
                                        StringRef(std::to_string(
                                        static_cast<expression*>(*item)->value)),
                                         10)));
            }
            init = ConstantArray::get((ArrayType*) type, const_array);
            global = new GlobalVariable(*context->module,
                                        type,
                                        false,
                                        GlobalValue::PrivateLinkage,
                                        0,
                                        Twine("." + (*it)->id));
            global->setInitializer(init);
          }
        }
        break;
      }

      case basic_type::BOOLEAN: {
        type = Type::getInt1Ty(getGlobalContext());
        if ((*it)->is_array_type) {
          type = PointerType::get(IntegerType::get(getGlobalContext(),
                                                 1),
                                (*it)->size->value);
          init = ConstantAggregateZero::get(type);
          
          if ((*it)->initializer_list) {
            std::vector<Constant*> const_array;
            for (auto item = (*it)->initializer_list->begin();
                 item != (*it)->initializer_list->end();
                 item++) {

              const_array.push_back(ConstantInt::get(
                                      getGlobalContext(),
                                      APInt(1,
                                        StringRef(std::to_string(
                                        static_cast<expression*>(*item)->value)),
                                         10)));
            }
            init = ConstantArray::get((ArrayType*) type, const_array);
            global = new GlobalVariable(*context->module,
                                        type,
                                        false,
                                        GlobalValue::PrivateLinkage,
                                        0,
                                        Twine("." + (*it)->id));

            global->setInitializer(init);
          }
        }
        break;
      }

      default:
        break;
      }
      
      local = new AllocaInst(type,
                             (*it)->id.c_str(),
                             context->current_block());

      if ((*it)->initializer) {
        init = (Constant*) (*it)->initializer->emit_ir_code(context);
        if ((*it)->type == basic_type::STRING) {
          std::vector<Constant*> idx;
          idx.push_back(ConstantInt::get(getGlobalContext(),
                                         APInt(32, StringRef("0"), 10)));
          idx.push_back(ConstantInt::get(getGlobalContext(),
                                         APInt(32, StringRef("0"), 10)));
          
          init = ConstantExpr::getGetElementPtr(
                   ArrayType::get(IntegerType::get(getGlobalContext(),8), 
                                  (*it)->
                                  initializer->
                                  string_value.size() + 1),
                   init,
                   idx);
        }
        store = new StoreInst(init,
                              local,
                              false,
                              context->current_block());
      }
      
      if ((*it)->initializer_list) {
        context->locals()[(*it)->id] = global;
        var = global;
      } else {
        context->locals()[(*it)->id] = local;
        var = local;
      }
      
    }
  } 
  return var;

}


