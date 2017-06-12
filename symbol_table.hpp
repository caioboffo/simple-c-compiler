#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <map>
#include <list>


enum class symbol_type_t
{
  INTEGER, BOOLEAN, STRING, FUNCTION, PROCEDURE
    };

enum class scope_type_t
{
  GLOBAL, LOCAL, FORMAL
    };

typedef struct scope_t
{
  int id;
  scope_type_t scope_type;
  symbol_type_t symbol_type;
} scope ;

typedef std::map<std::string, std::list<scope>* > symbol_table_t;
typedef symbol_table_t::iterator symbol;

typedef struct symbol_status_t
{
  bool already_exists;
  symbol reference;
} *sym_status;

class symbol_table {

  // private member
  symbol_table_t *_table;
  
public:
  symbol_table();
  sym_status insert(std::string id);
  
};

#endif /* SYMBOL_TABLE_H */
