#ifndef BREAK_STMT_H
#define BREAK_STMT_H

#include "statement.hpp"

class break_stmt : public statement {
public:
  break_stmt() {}
  void print();
  void evaluate();
};
  

#endif /* BREAK_STMT_H */
