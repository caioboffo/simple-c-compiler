#include <iostream>
#include <vector>

#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constants.h>
#include "llvm/IR/CallingConv.h"
#include <llvm/IR/Constant.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/ADT/Twine.h>

#include "symbol_declaration.hpp"
#include "subprogram_declaration.hpp"
#include "codegen_context.hpp"
#include "symbol_table.hpp"
#include "error_manager.hpp"

subprogram_declaration::subprogram_declaration
                       (basic_type             t,
                        std::string            id,
                        std::list<tree_node*> *parameters,
                        tree_node             *compound_statement,
                        YYLTYPE loc) {

  this->return_type = t;
  this->name   = new symbol(id);
  this->param_list = new std::list<symbol_declaration*>();
  for (auto it = parameters->begin();
       it != parameters->end();
       it++) {
    this->param_list->push_back(static_cast<symbol_declaration*>(*it));
  }
  this->block = static_cast<basic_block*>(compound_statement);
  this->block->return_type = this->return_type;
  this->block->parent = this;
  this->locations = loc;

}

subprogram_declaration::subprogram_declaration
                       (std::string            id,
                        std::list<tree_node*> *parameters,
                        tree_node             *compound_statement,
                        YYLTYPE loc) {

  this->return_type = basic_type::VOID;
  this->name   = new symbol(id);
  this->param_list = new std::list<symbol_declaration*>();
  for (auto it = parameters->begin();
       it != parameters->end();
       it++) {
    this->param_list->push_back(static_cast<symbol_declaration*>(*it));
  }
  this->block = static_cast<basic_block*>(compound_statement);
  this->block->return_type = this->return_type;
  this->block->parent = this;
  this->locations = loc;

}

void subprogram_declaration::print() {
  std::cout << to_string(return_type) << " ";
  name->print();
  std::cout <<  "(";
  int i = 1;
  if (param_list->size() > 0) {
    for (auto param = param_list->begin();
         param != param_list->end();
         param++, i++) {
      (*param)->print();
      if (i != param_list->size())
        std::cout << ", ";
    }
  }
  std::cout << ") \n";

  block->print();
}

void subprogram_declaration::evaluate() {
  #ifdef STATUS_OUTPUT 
  std::cout << "evaluating subprogram declaration\n";
  #endif

  #ifdef RETURN_STATUS
  std::cout << "subprogram returns "
            << to_string(this->return_type) << "\n";
  #endif
  
  if (this->return_type == basic_type::VOID) { 
    symbol_table::insert(this->name->id,
                         basic_type::PROCEDURE,
                         basic_type::VOID,
                         this->param_list,
                         this->locations);
  } else {
    symbol_table::insert(this->name->id,
                         basic_type::FUNCTION,
                         this->return_type,
                         this->param_list,
                         this->locations);

  }

  symbol_table::create_scope();

  // evaluate each parameter so it can be inserted to symbol table
  if (param_list->size() > 0) {
    for (auto param = param_list->begin();
         param != param_list->end();
         param++) {
      (*param)->evaluate();
    }
  }

  // evaluate the subprogram block
  block->evaluate();

  if (!block->return_stmt && this->return_type != basic_type::VOID) {
    std::string err = "missing return statement for function "
      + this->name->id;
    error_manager::error(err.c_str(), this->locations);
  }

  symbol_table::delete_scope();
}

Value *subprogram_declaration::emit_ir_code(codegen_context *context) {
  
  std::vector<Type*> func_args_type;
  FunctionType* func_type;
  Type* type;
  switch (this->return_type) {
  case basic_type::INTEGER: {
    type = IntegerType::get(getGlobalContext(), 32);
    break;
  }
  case basic_type::BOOLEAN: {
    type = IntegerType::get(getGlobalContext(), 1);
    break;
  } 
  case basic_type::STRING: {
    type = PointerType::get(
      IntegerType::get(getGlobalContext(), 8),
      0);

    break;
  }
  case basic_type::VOID: {
    type = Type::getVoidTy(getGlobalContext());
    break;
  }
  }

  for (auto param = this->param_list->begin();
       param != this->param_list->end();
       param++) {

    Type *t;
    switch ((*param)->type) {
    case basic_type::INTEGER: {
      if ((*param)->id_list->back()->is_array_type) {
        t = PointerType::get(IntegerType::get(
                                              getGlobalContext(),
                                              32), 0);

      } else 
        t = IntegerType::get(getGlobalContext(), 32);
      break;

    }
    case basic_type::BOOLEAN: {
      if ((*param)->id_list->back()->is_array_type) {
        t = PointerType::get(IntegerType::get(
                                              getGlobalContext(),
                                              1), 0);

      } else 
        t = IntegerType::get(getGlobalContext(), 1);
      break;
    } 
    case basic_type::STRING: {
      t = PointerType::get(IntegerType::get(
                                            getGlobalContext(),
                                            8), 0);
      break;
    }
    }
    func_args_type.push_back(t);
    
  }

  func_type = FunctionType::get(
                type,
                func_args_type,
                false);

  
  Function* func = context->module->getFunction(this->name->id);
  if (!func) {
    func = Function::Create(func_type,
                            GlobalValue::ExternalLinkage,
                            this->name->id,
                            context->module); 
    func->setCallingConv(CallingConv::C);
  }

  if (symbol_table::current_scope_num == 0) {
    context->globals[name->id] = func;
  } else {
    context->locals()[name->id] = func;
  }

  auto param = param_list->begin();
  for (auto args = func->arg_begin();
       args != func->arg_end();
       args++, param++) {
    args->setName((*param)->id_list->back()->id);
  }
  
  BasicBlock *basic_block = BasicBlock::Create(getGlobalContext(),
                                               "",
                                               func,
                                               0);
  context->push_block(basic_block);
  
  symbol_table::create_scope();
  
  param = param_list->begin();
  auto ty = func_args_type.begin();
  for (auto args = func->arg_begin();
       args != func->arg_end();
       args++, param++, ty++) {
    AllocaInst *ptr = new AllocaInst((*ty), "",
                                     context->current_block());
    StoreInst *str = new StoreInst(&(*args),
                                   ptr,
                                   false,
                                   context->current_block());
    context->locals()[(*param)->id_list->back()->id] = ptr;
  }

  block->emit_ir_code(context);
  
  symbol_table::delete_scope();
  if (this->return_type == basic_type::VOID && !block->return_stmt)
    ReturnInst::Create(getGlobalContext(), basic_block);

  // neste ponto remover todos os blocos empilhados
  // acima de basic_block; ou seja
  // remover todas as variáveis armazenadas nos escopos
  // criados a partir deste.
  
  //context->pop_block();

  return func;
}
