#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <iostream>
#include <string>

extern char *filename;
extern bool any_errors;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


class tree_node {
protected:
  YYLTYPE locations;
  void error(char const *msg) {
  if (!any_errors)
    any_errors = true;

  std::cerr << filename
            << " " << this->locations.first_line
            << ":" << this->locations.first_column
            << "-" << this->locations.last_column
            << "\033[1;31m error: \033[0m"
            << msg << "\n";
  
}



public:
  virtual void print() {}
  virtual void evaluate() {}
};

#endif /* TREE_NODE_H */
