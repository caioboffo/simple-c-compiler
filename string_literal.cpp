#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/Instructions.h>
#include <llvm/ADT/Twine.h>

#include "string_literal.hpp"
#include "basic_type.hpp"
#include "codegen_context.hpp"

string_literal::string_literal(std::string str) {
  this->string_value = str.substr(1, str.size()-2);
  set_type(basic_type::STRING);
}

string_literal::string_literal(std::string str, YYLTYPE loc) {
  this->string_value = str.substr(1, str.size()-2);
  set_type(basic_type::STRING);
  this->locations = loc;
}
void string_literal::print() {
  if (string_value.length()) 
    std::cout << this->string_value ;
  else
    std::cout << "NULL";
}

void string_literal::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a string literal " << this->string_value << "\n";
  #endif
}

Value *string_literal::emit_ir_code(codegen_context *context) {
  ArrayType *array_ty
    = ArrayType::get(IntegerType::get(getGlobalContext(), 8),
                     string_value.size() + 1);
                         
  GlobalVariable *gvar_array_str
    = new GlobalVariable(*context->module,
                         array_ty,
                         true,
                         GlobalValue::PrivateLinkage,
                         0, ".str");
                         
  Constant *const_array = ConstantDataArray::getString(getGlobalContext(),
                                                       string_value,
                                                       true);
                                                       
  gvar_array_str->setInitializer(const_array);

  return gvar_array_str;
}
