#include "codegen_context.hpp"
#include "error_manager.hpp"

std::string base_name(std::string const & path)
{
  return path.substr(path.find_last_of("/\\") + 1);
}

codegen_context::codegen_context() {
  blocks = new std::deque<codegen_block*>();
  module = new Module(base_name(error_manager::filename) + ".bc",
                      getGlobalContext());
}

Value* codegen_context::find(std::string name) {

  for (auto block = blocks->begin();
       block != blocks->end();
       block++) {
    if ((*block)->locals.find(name) != (*block)->locals.end())
      return (*block)->locals[name];
  }
  if (globals.find(name) != globals.end())
    return globals[name];

  return NULL;

}

BasicBlock *codegen_context::current_block() {
  return blocks->front()->block;
}

void codegen_context::set_parent(Function *v) {
  blocks->front()->parent = v;
}

Function *codegen_context::get_parent() {
  return blocks->front()->parent;
}

void codegen_context::push_block(BasicBlock *block) {
  blocks->push_front(new codegen_block());
  blocks->front()->return_value = NULL;
  blocks->front()->block = block;
}

void codegen_context::pop_block() {
  codegen_block *top = blocks->front();
  blocks->pop_front();
  delete top;
}

void codegen_context::set_current_return_value(Value *value) {
  blocks->front()->return_value = value;
}

Value *codegen_context::get_current_return_value() {
  return blocks->front()->return_value;
}
