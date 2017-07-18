#include "module_operation.hpp"
#include "error_manager.hpp"
#include <llvm/IR/Instruction.h>
#include <llvm/IR/InstrTypes.h>

void module_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " % ";
  right->print();
  std::cout << ")";
}

void module_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating % operation\n";
  #endif

  this->left->evaluate();
  this->right->evaluate();

  if (this->left->type  == basic_type::INTEGER &&
      this->right->type == basic_type::INTEGER) {
    this->type = basic_type::INTEGER;
    this->value = this->left->value % this->right->value;
  }
  else
    error_manager::error("incompatible types", this->locations);  

}

Value *module_operation::emit_ir_code(codegen_context *context) {
  return BinaryOperator::Create(Instruction::SRem,
                                left->emit_ir_code(context),
                                right->emit_ir_code(context),
                                "",
                                context->current_block());
                                

}
