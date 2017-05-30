#include "times_operation.hpp"

void times_operation::print() {
  std::cout << "(";
  left->print();
  std::cout << " * ";
  right->print();
  std::cout << ")";
}

void times_operation::evaluate() {
  std::cout << "evaluating a * operation ...\n";

}
