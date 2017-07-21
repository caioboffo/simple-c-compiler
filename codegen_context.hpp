#ifndef CODEGEN_CONTEXT_H
#define CODEGEN_CONTEXT_H

#include <string>
#include <deque>
#include <map>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/BasicBlock.h>

using namespace llvm;

class codegen_context {
  
  class codegen_block {
  public:
    BasicBlock *block;
    Value      *return_value;
    std::map<std::string, Value*> locals;
  };

  std::deque<codegen_block*> *blocks;

 public:
  Function *write_function;
  Function *read_function;

  bool inner_break;
  std::map<std::string, Value*> globals;
  std::deque<BasicBlock*> exit_blocks;
  
  Module *module;
  codegen_context();
  BasicBlock *current_block();
  std::map<std::string, Value*>& locals() { return blocks->front()->locals; }
  Value*      find(std::string name);
  void        push_block(BasicBlock *block);
  void        push_exit_block(BasicBlock *block);
  BasicBlock *current_exit_block();
  void        pop_exit_block();
  void        pop_block();
  void        set_current_return_value(Value *value);
  Value*      get_current_return_value();
 
};

#endif /* CODEGEN_CONTEXT_H */
