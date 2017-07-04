#ifndef ERROR_MANAGER_H
#define ERROR_MANAGER_H

#include <iostream>
#include "locations.hpp"

class error_manager {
private:
  static bool any_errors;

public:
  static char *filename;
  static bool had_error();
  static void error(char const *msg, YYLTYPE location);
    
};

#endif /* ERROR_MANAGER_H */
