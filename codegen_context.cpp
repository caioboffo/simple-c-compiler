#include "codegen_context.hpp"
#include "error_manager.hpp"

std::string base_name(std::string const & path)
{
  return path.substr(path.find_last_of("/\\") + 1);
}

codegen_context::codegen_context() {
  blocks = new std::stack<codegen_block*>();
  module = new Module(base_name(error_manager::filename) + ".bc",
                      getGlobalContext());
}
 
BasicBlock *codegen_context::current_block() {
  return blocks->top()->block;
}

void codegen_context::push_block(BasicBlock *block) {
  blocks->push(new codegen_block());
  blocks->top()->return_value = NULL;
  blocks->top()->block = block;
}

void codegen_context::pop_block() {
  codegen_block *top = blocks->top();
  blocks->pop();
  delete top;
}

void codegen_context::set_current_return_value(Value *value) {
  blocks->top()->return_value = value;
}

Value *codegen_context::get_current_return_value() {
  return blocks->top()->return_value;
}
