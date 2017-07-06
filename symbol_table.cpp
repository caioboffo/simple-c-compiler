#include "symbol_table.hpp"
#include "error_manager.hpp"
#include "symbol.hpp"

int symbol_table::current_scope_num;
symbol_table::symbol_table_t *symbol_table::_table;

void symbol_table::create_symbol_table() {
  _table            = new symbol_table_t();
  current_scope_num = 0;
}

void symbol_table::delete_symbol_table() {}

// Add symbol to name table
void symbol_table::insert(std::string id) {
  _table->emplace(id, new std::list<scope*>());
}

// Add symbol to symbol table
void symbol_table::insert(std::string name,
                          basic_type type,
                          symbol_info *si,
                          YYLTYPE locations) {

  scope       *ns = new scope(current_scope_num, si);
  auto sym = _table->find(name);
  // if found
  if (sym != _table->end()) {
    // is same escope? should give a symbol redeclaration error
    if ((*sym).second->size() > 0) {
      if (((*sym).second->back())->num == current_scope_num) {
        std::string err = "redefinition of name " + name;
        error_manager::error(err.c_str(), locations);
      } else {
        (*sym).second->push_back(ns);
      }
    } else { // insert the new scope information at the back of the list
        (*sym).second->push_back(ns);
    }
  }
  // otherwise if not found (should not happend) 
  else {
    _table->emplace(name, new std::list<scope*>({ns}));
  }
}

void symbol_table::insert(std::string name,
                          basic_type type,
                          int value,
                          YYLTYPE locations) {

  symbol_value sv;
  if (type == basic_type::INTEGER)
    sv.i_val = value;
  else if (type == basic_type::BOOLEAN)
    sv.b_val = value;

  symbol_info *si =  new symbol_info(type, sv);
  insert(name, type, si, locations);
}

void symbol_table::insert(std::string name,
                          basic_type type,
                          std::string value,
                          YYLTYPE locations) {
  symbol_value sv;
  sv.s_val = value;
  symbol_info *si =  new symbol_info(type, sv);
  insert(name, type, si, locations);
}

void symbol_table::insert(std::string name,
                          basic_type type,
                          basic_type return_type,
                          std::list<tree_node*> *param_list,
                          YYLTYPE locations) {
  
  std::list<basic_type> *p = new std::list<basic_type>();
  
  for (auto it = param_list->begin();
       it != param_list->end();
       it++) {
    p->push_back(static_cast<symbol*>(*it)->type);
  }
  
  symbol_info *si = new symbol_info(type, return_type, p);
  insert(name, type, si, locations);
  
}

bool symbol_table::lookup(std::string name) {
  auto sym = _table->find(name);
  
  if (sym != _table->end()) {
    if ((*sym).second->size() > 0) {
      if (((*sym).second->back()->info->type == basic_type::PROCEDURE) ||
          ((*sym).second->back()->info->type == basic_type::FUNCTION ))
        return true;
    }
  }
  return false;
}

symbol_table::symbol_info* symbol_table::lookup(std::string name,
                                                YYLTYPE locations) {
  symbol_info *si;
  auto sym = _table->find(name);

  if (sym != _table->end()) 
    if ((*sym).second->size() > 0) {
      si = ((*sym).second->back())->info;
      return si;
    }
    
  std::string err = "undefined reference to " + name;
  error_manager::error(err.c_str(), locations);
  si = new symbol_info(basic_type::ERROR);
  return si;
}

void symbol_table::create_scope() {
  current_scope_num++;
}

void symbol_table::delete_scope() {
  for (auto sym = _table->begin();
       sym != _table->end();
       sym++) {
    if ((*sym).second->size() > 0) {
      if (((*sym).second->back())->num == current_scope_num)
        // remove the head of scope list that contain current scope names
        (*sym).second->pop_back();
    }
  }
  current_scope_num--;
}
