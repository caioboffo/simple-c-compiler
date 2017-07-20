#include "unary_minus_operation.hpp"
#include "expression.hpp"
#include "error_manager.hpp"
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/InstrTypes.h>

void unary_minus_operation::print() {
  std::cout << "-";
  exp->print();
}

void unary_minus_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a unary minus operation\n";
  #endif

  exp->evaluate();

  if (exp->type == basic_type::INTEGER) {
    this->type = exp->type;
    this->value = -this->value;
  }
  else
    error_manager::error("incompatible types", this->locations);  

}

Value *unary_minus_operation::emit_ir_code(codegen_context *context) {
  ConstantInt *zero = ConstantInt::get(getGlobalContext(),
                                       APInt(32, StringRef("0"), 10));
  return BinaryOperator::Create(Instruction::Sub,
                                zero,
                                exp->emit_ir_code(context),
                                "",
                                context->current_block());
}

