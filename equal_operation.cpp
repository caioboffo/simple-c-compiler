#include "equal_operation.hpp"
#include "error_manager.hpp"
#include <llvm/IR/Instructions.h>
#include <llvm/IR/InstrTypes.h>

void equal_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " == ";
  right->print();
  std::cout << ")";
}

void equal_operation::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating == operation\n";
  #endif

  this->left->evaluate();
  this->right->evaluate();

  if (this->left->type  == this->right->type) {
    this->type = basic_type::BOOLEAN;
    this->value = this->left->value == this->right->value;
  }
  else
    error_manager::error("incompatible types", this->locations);  
}

Value *equal_operation::emit_ir_code(codegen_context *context) {
  return new ICmpInst(*context->current_block(),
                      ICmpInst::ICMP_EQ,
                      left->emit_ir_code(context),
                      right->emit_ir_code(context));
}
