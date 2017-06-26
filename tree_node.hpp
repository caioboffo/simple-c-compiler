#ifndef TREE_NODE_H
#define TREE_NODE_H

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

#include <string>

class tree_node {
protected:
  YYLTYPE locations;
public:
  virtual void print() {}
  virtual void evaluate() {}
};

#endif /* TREE_NODE_H */
