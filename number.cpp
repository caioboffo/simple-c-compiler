#include <string>
#include <llvm/IR/Constants.h>
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

llvm::Value *number::emit_ir_code() {
  return llvm::ConstantInt::get(llvm::getGlobalContext(),
                                llvm::APInt(32,
                                            llvm::StringRef(std::to_string(this->value)),
                                            10));
}
