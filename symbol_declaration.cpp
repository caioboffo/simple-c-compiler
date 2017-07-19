#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/Instructions.h>
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

  for (auto it = this->id_list->begin();
       it != this->id_list->end();
       it++) {
    GlobalVariable *g_var;
    AllocaInst *alloc;
    if (symbol_table::current_scope_num == 0) {

      if ((*it)->type == basic_type::STRING) {
        if ((*it)->initializer) {
          ArrayType* _array
            = ArrayType::get(
                             IntegerType::get(getGlobalContext(), 8),
                             (*it)->initializer->string_value.size()+1);
          g_var
            = new GlobalVariable(
                                 *context->module,
                                 _array,
                                 false,
                                 GlobalValue::ExternalLinkage,
                                 0,
                                 Twine((*it)->id));

          g_var->setInitializer(static_cast<Constant*>(
                 (*it)->initializer->emit_ir_code(context)));
        
        } else  {
          g_var =
            new GlobalVariable(
                               *context->module,
                               PointerType::get(IntegerType::get(
                                 getGlobalContext(), 8), 0),
                               false,
                               GlobalValue::ExternalLinkage,
                               0,
                               Twine((*it)->id));
          g_var->setInitializer(ConstantInt::get(getGlobalContext(),
                                                 APInt(32, 0)));
        
        }
      } else { // is not a string
        if ((*it)->is_array_type) {
          ArrayType* _array
            = ArrayType::get(
                             IntegerType::get(getGlobalContext(), 32),
                             (*it)->size->value);
          g_var = new GlobalVariable(
                                   *context->module,
                                   _array,
                                   false,
                                   GlobalValue::ExternalLinkage,
                                   0,
                                   Twine((*it)->id));

          if ((*it)->initializer_list) {

            std::vector<Constant*> const_array_elems;
            for (auto item = (*it)->initializer_list->begin();
                 item != (*it)->initializer_list->end();
                 item++) {

              const_array_elems.push_back(ConstantInt::get(
                         getGlobalContext(),
                         APInt(32,
                               StringRef(std::to_string(
                                static_cast<expression*>(*item)->value)),
                               10)));
            }

            Constant* const_array
              = ConstantArray::get(_array,
                                   const_array_elems);

            g_var->setInitializer(const_array);
          

          }
          else  {
            Constant* const_array_zero
              = ConstantAggregateZero::get(_array);
            g_var->setInitializer(const_array_zero);

          }
        
        } else {        
          g_var = new GlobalVariable(
                                   *context->module,
                                   IntegerType::get(getGlobalContext(), 32),
                                   false,
                                   GlobalValue::ExternalLinkage,
                                   0,
                                   Twine((*it)->id));
      
          if ((*it)->initializer) {
            g_var->setInitializer(
              static_cast<Constant*>((*it)->
                                     initializer->
                                     emit_ir_code(context)));
          } else {
            g_var->setInitializer(ConstantInt::get(getGlobalContext(),
                                                 APInt(32, 0)));
          }

        }
      }
      context->globals[(*it)->id] = g_var;
      var = g_var;
    } else { // inner scopes g_var dec
      //////-----------------------------------------------------
      Type *type;

      if ((*it)->type == basic_type::STRING) {
        if ((*it)->initializer) {
         
        
        } else  {
        
        }
      } else { // is not a string
        if ((*it)->is_array_type) {
          type = ArrayType::get(IntegerType::get(getGlobalContext(), 32),
                                (*it)->size->value);

          alloc = new AllocaInst(type,
                                 (*it)->id.c_str(),
                                 context->current_block());


          if ((*it)->initializer_list) {
            std::vector<Constant*> const_array_elems;
            for (auto item = (*it)->initializer_list->begin();
                 item != (*it)->initializer_list->end();
                 item++) {

              const_array_elems.push_back(ConstantInt::get(
                         getGlobalContext(),
                         APInt(32,
                               StringRef(std::to_string(
                                static_cast<expression*>(*item)->value)),
                               10)));
            }

            alloc = new AllocaInst(type,
                                   (*it)->id.c_str(),
                                   context->current_block());

          }
          else  {

          }
        
        } else {        
          type = Type::getInt32Ty(getGlobalContext());

          alloc = new AllocaInst(type,
                                 (*it)->id.c_str(),
                                 context->current_block());
          
          if ((*it)->initializer) {
            StoreInst *store
              = new StoreInst((*it)->initializer->emit_ir_code(context),
                              alloc,
                              false,
                              context->current_block());
          }
        }
      }
      context->locals()[(*it)->id] = alloc;
      var = alloc;
    }
  }
  return var;

}


