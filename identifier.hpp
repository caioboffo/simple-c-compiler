#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <iostream>
#include <cstring>
#include "expression.hpp"

class identifier : public expression {
  std::string id;
  int         evaluated_size;
  expression *size;
  expression *initializer;
public:
  identifier(std::string id) : id(id) {}
  identifier(std::string id,
             expression *size) : id(id),
                                 size(size) {}
  identifier(identifier *var, expression *init);
  void set_type(int t);
  void print();
  int evaluate();
};


#endif /* IDENTIFIER_H */
