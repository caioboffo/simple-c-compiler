#ifndef BASIC_TYPE_H
#define BASIC_TYPE_H

enum class basic_type : char
{
     ERROR     = 0,
     INTEGER   ,
     BOOLEAN   ,
     STRING    ,
     VOID      ,
     FUNCTION  ,
     PROCEDURE    
};

inline std::string to_string(basic_type t) {
  switch (t) {
  case basic_type::INTEGER: {
    return "integer";
    break;
  }
  case basic_type::BOOLEAN: {
    return "boolean";
    break;
  }
  case basic_type::STRING: {
    return "string";
    break;
  }
  case basic_type::VOID: {
    return "void";
    break;
  }
  case basic_type::FUNCTION:
  case basic_type::PROCEDURE: {
    return "subprogram";
    break;
  }
  default:
    return "";
    break;
  }
}




#endif /* BASIC_TYPE_H */
