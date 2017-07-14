#ifndef CODEGEN_CONTEXT_H
#define CODEGEN_CONTEXT_H

#include <stack>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/BasicBlock.h>

using namespace llvm;

class codegen_context {
  
  class codegen_block {
  public:
    BasicBlock *block;
    Value      *return_value;
  };

  std::stack<codegen_block*> *blocks;

 public:
  
  Module *module;
  codegen_context();
  BasicBlock *current_block();
  void        push_block(BasicBlock *block);
  void        pop_block();
  void        set_current_return_value(Value *value);
  Value*      get_current_return_value();
 
};

#endif /* CODEGEN_CONTEXT_H */
