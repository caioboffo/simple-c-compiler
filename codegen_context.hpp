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
    Function   *parent;
    std::map<std::string, Value*> locals;
  };

  std::deque<codegen_block*> *blocks;

 public:
  Function *write_function;
  Function *read_function;

  std::map<std::string, Value*> globals;  
  Module *module;
  codegen_context();
  BasicBlock *current_block();
  std::map<std::string, Value*>& locals() { return blocks->front()->locals; }
  Value*      find(std::string name);
  void        push_block(BasicBlock *block);
  Function*   get_parent();
  void        set_parent(Function *v);
  void        pop_block();
  void        set_current_return_value(Value *value);
  Value*      get_current_return_value();
 
};

#endif /* CODEGEN_CONTEXT_H */
