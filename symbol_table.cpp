#include "symbol_table.hpp"

symbol_table::symbol_table() {
  _table = new symbol_table_t();
}

sym_status symbol_table::insert(std::string id) {

  sym_status status = new symbol_status_t();
  auto ret = _table->emplace(id, new std::list<scope>());

  status->already_exists = !(ret.second);
  status->reference = ret.first;
  
  return status;
  
}
