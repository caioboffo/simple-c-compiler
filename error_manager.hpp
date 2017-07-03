#ifndef ERROR_MANAGER_H
#define ERROR_MANAGER_H

#include <iostream>
#include "locations.hpp"


class error_manager {
private:
  static bool any_errors;

public:
  static char *filename;
  static bool had_error() { return any_errors; }

  static void error(char const *msg, YYLTYPE location) {
    if (!any_errors)
      any_errors = true;

    std::cerr << filename
              << " " << location.first_line
              << ":" << location.first_column
              << "-" << location.last_column
              << "\033[1;31m error: \033[0m"
              << msg << "\n";
  }


    
};

#endif /* ERROR_MANAGER_H */
