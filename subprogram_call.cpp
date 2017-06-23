#include <iostream>
#include "subprogram_call.hpp"
#include "symbol.hpp"

subprogram_call::subprogram_call(std::string id, std::list<tree_node*> *param) {
  identifier = new symbol(id);
  parameters = param;
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
}
