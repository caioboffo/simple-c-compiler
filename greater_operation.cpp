#include "greater_operation.hpp"
#include "error_manager.hpp"
#include <llvm/IR/Instructions.h>
#include <llvm/IR/InstrTypes.h>

void greater_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " > ";
  right->print();
  std::cout << ")";
}

void greater_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating > operation\n";
  #endif

  this->left->evaluate();
  this->right->evaluate();

  if (this->left->type  == basic_type::INTEGER &&
      this->right->type == basic_type::INTEGER) {
    this->type = basic_type::BOOLEAN;
    this->value = this->left->value > this->right->value;
  }
  else
    error_manager::error("incompatible types", this->locations);  

}

Value *greater_operation::emit_ir_code(codegen_context *context) {
  return new ICmpInst(*context->current_block(),
                      ICmpInst::ICMP_SGT,
                      left->emit_ir_code(context),
                      right->emit_ir_code(context));
}
