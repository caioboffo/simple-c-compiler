#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <iostream>
#include <cstring>
#include "expression.hpp"

class identifier : public expression {
  std::string id;
public:
  identifier(std::string id) : id(id) {}
  void print();
  int evaluate();
};


#endif /* IDENTIFIER_H */
