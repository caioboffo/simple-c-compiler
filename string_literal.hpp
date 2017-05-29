#ifndef STRING_LITERAL_H
#define STRING_LITERAL_H

#include <iostream>
#include <cstring>
#include "expression.hpp"

class string_literal : public expression {
  std::string string_value;
public:
  string_literal(std::string str);
  void print();
  int evaluate();
};

#endif /* STRING_LITERAL_H */
