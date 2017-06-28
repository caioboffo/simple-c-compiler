#include <string>
#include "symbol_table.hpp"
#include "error_manager.hpp"
#include "locations.hpp"

symbol_table::symbol_table() {
  current_scope = 0;
  _table = new symbol_table_t();
}

// Add symbol to name table
void symbol_table::insert(std::string id) {
  _table->emplace(id, new std::list<scope*>());
}

// Add symbol to symbol table
void symbol_table::insert(std::string id,
                          scope_type scope_t,
                          symbol_type sym_t,
                          YYLTYPE locations) {

  scope *ns = new scope(current_scope, scope_t, sym_t);
  
  auto sym = _table->find(id);
  // if found
  if (sym != _table->end()) {
    // is same escope? should give a symbol redeclaration error
    if (((*sym).second->back())->id == current_scope) {
      std::string err = "redefinition of symbol " + id;
      error_manager::error(err.c_str(), locations);
    } else { // insert the new scope information at the back of the list
      (*sym).second->push_back(ns);
    } 
  }
  // otherwise if not found (should not happend) 
  else {
    _table->emplace(id, new std::list<scope*>({ns}));
  }
}

void symbol_table::new_scope() {
  current_scope++;
}

