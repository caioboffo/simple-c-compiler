#ifndef CORE_FUNCTIONS_H
#define CORE_FUNCTIONS_H

#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Constants.h>

#include "codegen_context.hpp"

using namespace llvm;

void create_printf_function(codegen_context *context) {
  PointerType* ptr = PointerType::get(IntegerType::get(context->module->getContext(), 8)
                                      , 0);
  std::vector<Type*>funct_ty_args;
  funct_ty_args.push_back(ptr);
  FunctionType* func_ty = FunctionType::get(
    /*Result=*/IntegerType::get(getGlobalContext(), 32),
    /*Params=*/funct_ty_args,
    /*isVarArg=*/true);

  Function* func_printf = context->module->getFunction("printf");
    if (!func_printf) {
      func_printf = Function::Create(
        /*Type=*/func_ty,
        /*Linkage=*/GlobalValue::ExternalLinkage,
        /*Name=*/"printf", context->module); // (external, no body)
    func_printf->setCallingConv(CallingConv::C);
    }

    context->write_function = func_printf;
}

void create_read_function(codegen_context *context) {

}

void create_core_functions(codegen_context *context) {
  create_printf_function(context);
  create_read_function(context);
}

#endif /* CORE_FUNCTIONS_H */

