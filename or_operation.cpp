#include "or_operation.hpp"
#include "error_manager.hpp"
#include <llvm/IR/Instruction.h>
#include <llvm/IR/InstrTypes.h>

void or_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " || ";
  right->print();
  std::cout << ")";
}

void or_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating || operation\n";
  #endif

  this->left->evaluate();
  this->right->evaluate();

  if (this->left->type  == basic_type::BOOLEAN &&
      this->right->type == basic_type::BOOLEAN) {
    this->type = basic_type::BOOLEAN;
    this->value = this->left->value || this->right->value;
  }
  else
    error_manager::error("incompatible types", this->locations);  

}

Value *or_operation::emit_ir_code(codegen_context *context) {
  return BinaryOperator::Create(Instruction::Or,
                                left->emit_ir_code(context),
                                right->emit_ir_code(context),
                                "",
                                context->current_block());
                                

}

