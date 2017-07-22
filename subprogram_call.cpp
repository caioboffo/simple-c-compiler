#include <iostream>
#include <sstream>
#include <vector>
#include "subprogram_call.hpp"
#include "symbol.hpp"
#include "symbol_table.hpp"
#include "error_manager.hpp"
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/InstrTypes.h>

subprogram_call::subprogram_call(std::string id,
                                 std::list<tree_node*> *param,
                                 YYLTYPE loc) {
  identifier = new symbol(id, loc);
  parameters = param;
  this->locations = loc;
}

void subprogram_call::print() {
  identifier->print();
  std::cout << "(";
  if (parameters->size() > 0) {
    int index = 1;
    for (auto param=parameters->begin();
         param != parameters->end();
         param++, index++) {
      (*param)->print();
      if (index != parameters->size())
        std::cout << ", ";
    }
  }
  std::cout << ")";
}

void subprogram_call::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating subprogram call\n";
  #endif

  symbol_table::symbol_info *si
    = symbol_table::lookup(this->identifier->id,
                           this->locations);

  this->type = si->return_type;

  // evaluate informed parameters 
  for (auto it = parameters->begin();
       it != parameters->end();
       it++) {
    (*it)->evaluate();
  }

  int total_informed_param = this->parameters->size();
  int total_declared_param = si->param_type->size();

  if (total_declared_param != total_informed_param) {
    std::ostringstream err;
    err << "Missing parameters at "
        << this->identifier->id
        << " declared "
        << total_declared_param
        << " informed " 
        << total_informed_param;
    error_manager::error(err.str().c_str(), this->locations);
  } else {
    auto declared = si->param_type->begin();
    for (auto informed = this->parameters->begin();
         informed != this->parameters->end();
         declared++, informed++) {
      if ((*declared) != static_cast<expression*>((*informed))->type) {
        std::ostringstream err;
        err << "wrong type of parameter: informed "
            << to_string(static_cast<expression*>((*informed))->type)
            << " should be of type "
            << to_string((*declared)); 
        error_manager::error(err.str().c_str(), this->locations);
      }
      
    }
  }
  
}

Value *subprogram_call::emit_ir_code(codegen_context *context) {
  std::vector<Value*> params;

  for (auto e = parameters->begin();
       e != parameters->end();
       e++) {
      params.push_back(static_cast<expression*>(*e)->emit_ir_code(context));
  }
  
  return CallInst::Create(context->find(identifier->id),
                          params,
                          "",
                          context->current_block());
}
