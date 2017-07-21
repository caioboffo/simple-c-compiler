#include <iostream>
#include "while_stmt.hpp"
#include "error_manager.hpp"
#include "expression.hpp"
#include "basic_block.hpp"
#include "symbol_table.hpp"
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/InstrTypes.h>

void while_stmt::print() {
  std::cout << "while ";
  exp->print();
  std::cout << "\n";
  block->print();
}

void while_stmt::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a while statement\n";
  #endif
  symbol_table::push_accept_break();
  
  exp->evaluate();
  
  if (exp->type != basic_type::BOOLEAN)
    error_manager::error("while expression should be a logic expression",
                         this->locations);

  this->return_type 
    = static_cast<basic_block*>(this->parent)->return_type;
  
  #ifdef RETURN_STATUS
  std::cout << "while stmt returns " << to_string(this->return_type) << "\n";
  #endif

  block->return_type = this->return_type;
  
  symbol_table::create_scope();
  block->evaluate();
  symbol_table::delete_scope();
  
  static_cast<basic_block*>(this->parent)->return_stmt
    = block->return_stmt;

  symbol_table::pop_accept_break();

}

Value *while_stmt::emit_ir_code(codegen_context *context) {
  Function *parent = context->current_block()->getParent();

  BasicBlock *exp_block = BasicBlock::Create(getGlobalContext(),
                                             "",
                                             parent,
                                             0);
  BasicBlock *t_block = BasicBlock::Create(getGlobalContext(),
                                           "",
                                           parent,
                                           0);
  BasicBlock *exit_block = BasicBlock::Create(getGlobalContext(),
                                           "",
                                           parent,
                                           0);

  context->push_exit_block(exit_block);
  
  BranchInst::Create(exp_block, context->current_block());
  
  context->push_block(exp_block);
  BranchInst::Create(t_block,
                     exit_block,
                     exp->emit_ir_code(context),
                     context->current_block());
  context->pop_block();

  context->push_block(t_block);
  block->emit_ir_code(context);
  BranchInst::Create(exp_block, context->current_block());
  context->pop_block();

  // add new block
  context->push_block(exit_block);
 
  context->pop_exit_block();
  context->inner_break = false;
}
