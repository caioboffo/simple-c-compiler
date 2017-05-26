#include "program.hpp"

program::program(std::list<statement*> *stmtlist) : stmts(stmtlist) {}

void program::evaluate() {
  std::list<statement*>::iterator stmt_iter;
  for (stmt_iter = stmts->begin(); stmt_iter != stmts->end();
       stmt_iter++) {

    (*stmt_iter)->evaluate();
    (*stmt_iter)->print();
  }
}
