#include <iostream>
#include <sstream>
#include "subprogram_call.hpp"
#include "symbol.hpp"
#include "symbol_table.hpp"
#include "error_manager.hpp"

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

  symbol_table::symbol_info *si
    = symbol_table::lookup(static_cast<symbol*>(this->identifier)->id,
                           this->locations);

  this->type = si->return_type;

  // evaluate informed parameters 
  for (auto it = parameters->begin();
       it != parameters->end();
       it++) {
    (*it)->evaluate();
  }

  int total_informed_param = this->parameters->size();
  int total_declared_param = si->param_type->size();

  if (total_declared_param != total_informed_param) {
    std::ostringstream err;
    err << "Missing parameters at "
        << static_cast<symbol*>(this->identifier)->id
        << " declared "
        << total_declared_param
        << " informed " 
        << total_informed_param;
    error_manager::error(err.str().c_str(), this->locations);
  } else {
    auto declared = si->param_type->begin();
    for (auto informed = this->parameters->begin();
         informed != this->parameters->end();
         declared++, informed++) {
      if ((*declared) != static_cast<symbol*>((*informed))->type) {
        std::ostringstream err;
        err << "wrong type of parameter: informed "
            << to_string(static_cast<symbol*>((*informed))->type)
            << " should be of type "
            << to_string((*declared)); 
        error_manager::error(err.str().c_str(), this->locations);
      }
      
    }
  }
  // validar se a quantidade de paramentros informados
  // corresponde ao tipo e quantidade de parametros declarados
  
}
