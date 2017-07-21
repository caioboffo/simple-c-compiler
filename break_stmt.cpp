#include <iostream>
#include "break_stmt.hpp"
#include "symbol_table.hpp"
#include "error_manager.hpp"
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/InstrTypes.h>

void break_stmt::print() {
  std::cout << "break ";
}

void break_stmt::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a break \n";
  #endif
  if (!symbol_table::accept_break()) {
    error_manager::error("break statement outside of loop statement",
                         this->locations);
  }
    
}

Value *break_stmt::emit_ir_code(codegen_context* context) {
  context->inner_break = true;
  return BranchInst::Create(context->current_exit_block(),
                            context->current_block());

}
