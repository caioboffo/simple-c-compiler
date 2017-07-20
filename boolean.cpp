#include <llvm/IR/Constants.h>
#include <llvm/IR/LLVMContext.h>
#include "boolean.hpp"

boolean::boolean(int v, YYLTYPE loc) {
  this->value = v;
  set_type(basic_type::BOOLEAN);
  this->locations = loc;
}

void boolean::print() {
  if (value)
    std::cout << "true" ;
  else
    std::cout << "false" ;
}

void boolean::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a boolean type ...\n";
  #endif

}

Value *boolean::emit_ir_code(codegen_context *context) {
  return ConstantInt::get(getGlobalContext(),
                          APInt(1,
                                StringRef(std::to_string(this->value)),
                                10));
}
