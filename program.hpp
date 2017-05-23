#ifndef PROGRAM_H
#define PROGRAM_H

#include <list>
#include "statement.hpp"

class program {
  std::list<statement*> *stmts;

public:
  program(std::list<statement*> *stmtlist);
  void evaluate();
};

#endif /* PROGRAM_H */
