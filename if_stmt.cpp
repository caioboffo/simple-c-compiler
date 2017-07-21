#include <iostream>
#include "if_stmt.hpp"
#include "error_manager.hpp"
#include "expression.hpp"
#include "basic_block.hpp"
#include "symbol_table.hpp"
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/InstrTypes.h>


if_stmt::if_stmt(tree_node *exp,
                 tree_node *then_block,
                 YYLTYPE loc,
                 tree_node *else_block) {
  this->exp = static_cast<expression*>(exp);
  this->then_block = static_cast<basic_block*>(then_block);
  this->else_block = static_cast<basic_block*>(else_block);
  this->locations = loc;
}

void if_stmt::print() {
  std::cout << "if ";
  exp->print();
  std::cout << "\n";
  then_block->print();
  if (else_block) {
    std::cout << "\n";
    else_block->print();
  }
}

void if_stmt::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating an if statement\n";
  #endif

  exp->evaluate();
  
  if (this->exp->type != basic_type::BOOLEAN)
    error_manager::error("if expression should be a logic expression",
                         this->locations);

  this->return_type 
    = static_cast<basic_block*>(this->parent)->return_type;

  #ifdef RETURN_STATUS
  std::cout << "if stmt returns " << to_string(this->return_type) << "\n";
  #endif

  this->then_block->return_type = this->return_type;
  symbol_table::create_scope();
  then_block->evaluate();
  symbol_table::delete_scope();

  if (else_block) {
    this->else_block->return_type = this->return_type;
    symbol_table::create_scope();
    else_block->evaluate();
    symbol_table::delete_scope();

    if ((then_block->return_stmt && else_block->return_stmt) 
        && (then_block->return_type == else_block->return_type)) {
      static_cast<basic_block*>(this->parent)->return_stmt
        = then_block->return_stmt;
    }
  }
}

Value *if_stmt::emit_ir_code(codegen_context* context) {
  Function *parent = context->current_block()->getParent();
  
  BasicBlock *exit_block = BasicBlock::Create(getGlobalContext(),
                                              "",
                                              parent,
                                              0);

  BasicBlock *t_block = BasicBlock::Create(getGlobalContext(),
                                           "",
                                           parent,
                                           0);
  BasicBlock *f_block;
  
  if (else_block) {
     f_block = BasicBlock::Create(getGlobalContext(),
                                  "",
                                  parent,
                                  0);    
    BranchInst::Create(t_block,
                       f_block,
                       exp->emit_ir_code(context),
                       context->current_block());

  } else {
    BranchInst::Create(t_block,
                       exit_block,
                       exp->emit_ir_code(context),
                       context->current_block());

  }

  context->push_block(t_block);
  then_block->emit_ir_code(context);
  if (!context->inner_break) {
    BranchInst::Create(exit_block, context->current_block());
  }
  context->inner_break = false;
  context->pop_block();

  if (else_block) {
    context->push_block(f_block);
    else_block->emit_ir_code(context);
    if (!context->inner_break) {
      BranchInst::Create(exit_block, context->current_block());
    }
    context->inner_break = false;
    context->pop_block();
  }

  // add new block
  context->push_block(exit_block);

}
