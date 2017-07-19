#include <iostream>
#include "expression.hpp"
#include "return_stmt.hpp"
#include "basic_block.hpp"
#include "error_manager.hpp"
#include "subprogram_declaration.hpp"
#include <llvm/IR/Instructions.h>

void return_stmt::print() {
  std::cout << "return ";
  if (return_expression)
    return_expression->print();
}

void return_stmt::evaluate() {
  #ifdef STATUS_OUTPUT
  std::cout << "evaluating a return statement\n";
  #endif

  this->return_type = static_cast<basic_block*>(this->parent)->return_type;
  
  #ifdef RETURN_STATUS
  std::cout << "return stmt returns " << to_string(this->return_type) << "\n";
  #endif
  
  static_cast<basic_block*>(this->parent)->return_stmt = true;
  
  if (return_expression) {
    return_expression->evaluate();
    this->return_type = return_expression->type;
  } else
    this->return_type = basic_type::VOID;

  if (static_cast<basic_block*>(this->parent)->return_type
      != this->return_type) {
    std::string err = "cannot convert "
      + to_string(this->return_type) + " to "
      + to_string(static_cast<basic_block*>(this->parent)->return_type);
    error_manager::error(err.c_str(), this->locations);
  }
}

Value *return_stmt::emit_ir_code(codegen_context *context) {
  return ReturnInst::Create(getGlobalContext(),
                            ((return_expression) ?
                            return_expression->emit_ir_code(context) :
                             nullptr),
                            context->current_block());
}
