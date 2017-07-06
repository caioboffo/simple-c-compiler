#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <map>
#include <list>
#include "locations.hpp"
#include "tree_node.hpp"
#include "basic_type.hpp"

class symbol_table {
private:
  typedef struct symbol_value {
    int         i_val;
    int         b_val;
    std::string s_val;
  } symbol_value;

public:
  typedef struct symbol_info {
    basic_type               type;
    symbol_value             value;
    basic_type               return_type;
    std::list<basic_type>   *param_type;
    symbol_info(basic_type t) :
      type(t) {}
    symbol_info(basic_type   t,
                symbol_value s) :
      type(t),
      value(s) {}
    symbol_info(basic_type t,
                basic_type r,
                std::list<basic_type> *p) :
      type(t),
      return_type(r),
      param_type(p) {}
  } symbol_info;

private:
  
  

  typedef struct scope {
    int          num;
    symbol_info *info;
    scope(int i, symbol_info *info) :
      num(i), info(info) {}
  } scope;

  typedef std::map<std::string, std::list<scope*>* > symbol_table_t;
  typedef std::pair<std::string, std::list<scope*>*> sym_table_item;

  static void insert(std::string name,
                     basic_type type,
                     symbol_info *si,
                     YYLTYPE locations);

public:


  static symbol_table_t *_table;
  static int             current_scope_num;
  static void create_symbol_table();
  static void delete_symbol_table();

  static void insert(std::string name);
  static void insert(std::string name,
                     basic_type type,
                     int  value,
                     YYLTYPE locations);
  static void insert(std::string name,
                     basic_type type,
                     std::string string_value,
                     YYLTYPE locations);
  static void insert(std::string name,
                     basic_type type,
                     basic_type return_type,
                     std::list<tree_node*> *param_list,
                     YYLTYPE locations);

  static symbol_info* lookup(std::string name, YYLTYPE locations);
  static void create_scope();
  static void delete_scope();
};

#endif /* SYMBOL_TABLE_H */
