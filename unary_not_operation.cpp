#include "unary_not_operation.hpp"
#include "expression.hpp"
#include "error_manager.hpp"
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/InstrTypes.h>

void unary_not_operation::print() {
  std::cout << "!";
  exp->print();
}

void unary_not_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a unary not operation\n";
  #endif

  exp->evaluate();

  if (exp->type == basic_type::BOOLEAN) {
    this->type = exp->type;
    this->value = !this->value;
  }
  else
    error_manager::error("incompatible types", this->locations);  

}

Value *unary_not_operation::emit_ir_code(codegen_context *context) {

}
