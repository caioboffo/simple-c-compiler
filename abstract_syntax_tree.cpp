#include "abstract_syntax_tree.hpp"

void abstract_syntax_tree::evaluate() {
  std::list<tree_node*>::iterator nodelist_iterator;
  for (nodelist_iterator = nodes->begin();
       nodelist_iterator != nodes->end();
       nodelist_iterator++) {
    (*nodelist_iterator)->evaluate();
    (*nodelist_iterator)->print();
  }
}
