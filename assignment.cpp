#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/Instructions.h>
#include <llvm/ADT/Twine.h>

#include "expression.hpp"
#include "assignment.hpp"
#include "symbol.hpp"
#include "tree_node.hpp"
#include "symbol_table.hpp"
#include "error_manager.hpp"

void assignment::print() {
  id->print();
  std::cout << " = ";
  rhs->print();
}

void assignment::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating an assignment\n";
  #endif
  
  id->evaluate();
  if (id->type != basic_type::ERROR) {
    rhs->evaluate();

    if (id->type != rhs->type) {
      std::string err
        = "assignment for variable " + id->id
        + " should be of type " + to_string(id->type);
      error_manager::error(err.c_str(), this->locations);
    }
  }
  this->type = id->type;
  this->value = rhs->value;
  this->string_value = rhs->string_value;
  symbol_table::update_symbol_value(id->id,
                                    -1,
                                    this->value, this->string_value);
}

Value *assignment::emit_ir_code(codegen_context *context) {
  return new StoreInst(rhs->emit_ir_code(context),
                       context->find(id->id), false,
                       context->current_block());
}
