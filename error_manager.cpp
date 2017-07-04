#include "error_manager.hpp"

// static variable declaration 
bool error_manager::any_errors = false;
char *error_manager::filename;

bool error_manager::had_error() { return any_errors; }
void error_manager::error(char const *msg, YYLTYPE location) {
    if (!any_errors)
      any_errors = true;

    std::cerr << filename
              << " " << location.first_line
              << ":" << location.first_column
              << "-" << location.last_column
              << "\033[1;31m error: \033[0m"
              << msg << "\n";
  }

