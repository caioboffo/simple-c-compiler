#include <iostream>
#include "subprogram_call.hpp"
#include "symbol.hpp"

subprogram_call::subprogram_call(std::string id,
                                 std::list<tree_node*> *param,
                                 YYLTYPE loc) {
  identifier = new symbol(id, loc);
  parameters = param;
  this->locations = loc;
}

void subprogram_call::print() {
  identifier->print();
  std::cout << "(";
  if (parameters->size() > 0) {
    int index = 1;
    for (auto param=parameters->begin();
         param != parameters->end();
         param++, index++) {
      (*param)->print();
      if (index != parameters->size())
        std::cout << ", ";
    }
  }
  std::cout << ")";
}

void subprogram_call::evaluate() {
#ifdef STATUS_OUTPUT
  std::cout << "evaluating subprogram call\n";
#endif

  identifier->evaluate();
  this->type = static_cast<symbol*>(identifier)->type;
  
}
