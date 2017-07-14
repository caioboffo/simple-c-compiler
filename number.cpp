#include <string>
#include <llvm/IR/Constants.h>
#include <llvm/IR/LLVMContext.h>
#include "number.hpp"

number::number(int v, YYLTYPE loc) {
  this->value = v;
  set_type(basic_type::INTEGER);
  this->locations = loc;
}

void number::print() {
  std::cout << value ;
}

void number::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating number " << value << "\n";
  #endif
}

Value *number::emit_ir_code(codegen_context *context) {
  return ConstantInt::get(getGlobalContext(),
                          APInt(32,
                                StringRef(std::to_string(this->value)),
                                10));
}
