#include <sstream>
#include <iostream>
#include <vector>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/Instructions.h>
#include <llvm/ADT/Twine.h>

#include "write_stmt.hpp"

void write_stmt::print() {
  std::cout << "write ";
  int index = 1;
  for (auto it = expressions->begin();
       it != expressions->end();
       it++, index++) {
    (*it)->print();
    if (index != expressions->size())
      std::cout << ", ";
  }
}

void write_stmt::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating write statement\n";
  #endif
}

Value *write_stmt::emit_ir_code(codegen_context* context) {
  std::ostringstream constant_string;

  std::string digit_format = "%d";
  if (expressions->size() > 0) {
    for (auto e = expressions->begin();
         e != expressions->end();
         e++) {
      if ((*e)->type == basic_type::STRING)
        constant_string << (*e)->string_value;
      else
        constant_string << digit_format;
    }
  }
  constant_string << std::endl;

  ArrayType *array_ty = ArrayType::get(IntegerType::get(getGlobalContext(), 8),
                                       constant_string.str().size() + 1);
                         
  GlobalVariable *gvar_array_str
    = new GlobalVariable(*context->module,
                         array_ty,
                         true,
                         GlobalValue::PrivateLinkage,
                         0, ".str");
                         
  Constant *const_array = ConstantDataArray::getString(getGlobalContext(),
                                                       constant_string.str(),
                                                       true);
                                                       
  gvar_array_str->setInitializer(const_array);

  std::vector<Constant*> idx;
  idx.push_back(ConstantInt::get(getGlobalContext(),
                                 APInt(32, StringRef("0"), 10)));
  idx.push_back(ConstantInt::get(getGlobalContext(),
                                 APInt(32, StringRef("0"), 10)));

  Constant *const_ptr = ConstantExpr::getGetElementPtr(
    ArrayType::get(IntegerType::get(getGlobalContext(),8), 
                   constant_string.str().size() + 1),
    gvar_array_str,
    idx);

  std::vector<Value*> params;
  params.push_back(const_ptr);
  if (expressions->size() > 0) {
    for (auto e = expressions->begin();
         e != expressions->end();
         e++) {
      if ((*e)->type != basic_type::STRING)
        params.push_back((*e)->emit_ir_code(context));
    }
  }

  CallInst *printf_call = CallInst::Create(context->write_function,
                                           params,
                                           "",
                                           context->current_block());
  
  printf_call->setCallingConv(CallingConv::C);
  printf_call->setTailCall(false);
  
  return printf_call;
}
