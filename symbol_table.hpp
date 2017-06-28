#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <map>
#include <list>
#include "locations.hpp"

enum class symbol_type
{
  INTEGER, BOOLEAN, STRING, FUNCTION, PROCEDURE
};

enum class scope_type
{
  GLOBAL, LOCAL, FORMAL
};

typedef struct scope {
  int         id;
  scope_type  scope_t;
  symbol_type sym_t;
  scope(int i, scope_type scope_t, symbol_type sym_t) :
    id(i), scope_t(scope_t), sym_t(sym_t) {}
} scope;

typedef std::map<std::string, std::list<scope*>* > symbol_table_t;
typedef std::pair<std::string, std::list<scope*>*> sym_table_item;

class symbol_table {
  // private member
  symbol_table_t *_table;
  int current_scope;
public:

  symbol_table();
  void insert(std::string id);
  void insert(std::string id,
              scope_type scope_t,
              symbol_type sym_t,
              YYLTYPE locations);
  void new_scope();

};

#endif /* SYMBOL_TABLE_H */
