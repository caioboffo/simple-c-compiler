#include "and_operation.hpp"

void and_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " && ";
  right->print();
  std::cout << ")";
}

void and_operation::evaluate() {
  std::cout << "evaluating a && operation ...\n";

}
