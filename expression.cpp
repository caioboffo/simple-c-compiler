#include "expression.hpp"

void expression::set_type(int t) {
  this->type = t;
}

expression::expression() {
  value = 0;
}
