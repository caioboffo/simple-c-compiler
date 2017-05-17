/*
 * 
 * Copyright 2017 Caio Boffo Silva <caioboffo@gmail.com>
 * 
 * Parser for simple-c-language-compiler.
 * 
 */
%{

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstdarg>

extern int yylex(void);
extern int yylineno;
void yyerror(char const *, ...); 

void usage() {
  std::cout << "simple-c-compiler: fatal error: no input files" << std::endl;
  std::cout << "compilation terminated." << std::endl;
}
 
%}

%locations

%union {
  int    num;
  char   *str;
}

%token <ival> CONSTANT
%token <sval> STRING_LITERAL
%token <sval> IDENTIFIER

%token IF ELSE WHILE FOR BREAK RETURN READ WRITE
       INT BOOL STRING TRUE FALSE
       
%token PLUS_ASSIGN "+="
       MINUS_ASSIGN "-="
       TIMES_ASSIGN "*="
       OVER_ASSIGN "/=" 
       MOD_ASSIGN "%="
       GT ">"
       GE ">="
       LT "<"
       LE "<="
       EQ "=="
       NE "!="
       AND "&&"
       OR "||" 

%nonassoc THEN
%nonassoc ELSE

%left '='
%right '?' ':'
%left "||"
%left "&&"
%left "==" "!="
%left "<" "<=" ">" ">="
%left '+' '-'
%left '*' '/' '%'
%precedence NOT
%precedence NEG

/* Generate the parser description file.  */
%verbose
/* Enable run-time traces (YYDEBUG, YYERROR_VERBOSE).  */
%define parse.trace
%define parse.error verbose

%%

program : declaration_sequence
        ;
        
declaration_sequence
        : declaration
        | declaration declaration_sequence
        ;

declaration
        : var_dec
        | IDENTIFIER '(' param_list ')' compound_stmt
        | type_specifier IDENTIFIER '(' param_list ')' compound_stmt
        ;
        
param_list
        : param_seq
        | %empty
        ;

param_seq
        : param ',' param_seq
        | param
        ;

param
        : type_specifier IDENTIFIER
        | type_specifier IDENTIFIER '[' ']'
        ;
        
var_dec : type_specifier var_spec_seq ';'
        ;

var_spec_seq
        : var_spec ',' var_spec_seq
        | var_spec
        ;
        
var_spec
        : declarator '=' initializer
        | declarator
        ;
        
declarator
        : IDENTIFIER
        | IDENTIFIER '[' CONSTANT ']'
        ;

initializer
        : '{' literal_seq '}'
        | exp
        | assign
        ;
        
literal_seq
        : literal ',' literal_seq
        | literal
        ;
        
type_specifier
        : INT | BOOL | STRING ;

var_dec_list
        : var_dec var_dec_list
        | var_dec
        ;

stmt_list
        : stmt stmt_list
        | stmt
        ;
        
compound_stmt
        : '{' '}'
        | '{' var_dec_list stmt_list '}'
        | '{' var_dec_list '}'
        | '{' stmt_list '}'
        ;

stmt
        : selection_stmt
        | loop_stmt
        | jump_stmt
        | in_out_stmt
        | assign ';'
        | subprogram_call ';' 
        ;

selection_stmt
        : IF '(' exp ')' compound_stmt
        | IF '(' exp ')' compound_stmt ELSE compound_stmt
        ;

loop_stmt
        : WHILE '(' exp ')' compound_stmt
        | FOR '(' assign ';' exp ';' assign ')' compound_stmt
        ;

jump_stmt
        : RETURN ';'
        | RETURN exp ';' 
        | BREAK ';'  /* verificar se está dentro de um loop_stmt */
        ;

in_out_stmt
        : READ var ';'
        | WRITE expression_list ';'
        ;
        
subprogram_call
        : IDENTIFIER '(' expression_list ')' 
        ;
        
expression_list
        : expression_seq
        | %empty
        ;

expression_seq
        : initializer ',' expression_seq
        | initializer
        ;

assign  : var assign_operator exp 
        ;
        
assign_operator
        : '='
        | "+="
        | "-="
        | "*="
        | "/="
        | "%="
        ;
        
var     : IDENTIFIER
        | IDENTIFIER '[' exp ']'
        ;

literal : CONSTANT
        | STRING_LITERAL
        | TRUE
        | FALSE
        ;

exp
        : exp '+' exp
        | exp '-' exp
        | exp '*' exp
        | exp '/' exp
        | exp '%' exp
        | exp "<" exp
        | exp ">" exp
        | exp "<=" exp
        | exp ">=" exp
        | exp "&&" exp
        | exp "||" exp
        | exp "==" exp
        | exp "!=" exp
        | '!' exp %prec NOT
        | '-' exp %prec NEG
        | exp '?' exp ':' exp
        | var
        | literal
        | subprogram_call
        | '(' exp ')'
        ;

%%

void yyerror(char const *s, ...) {
  va_list ap;
  va_start(ap, s);

  if (yylloc.first_line)
     fprintf(stderr, "\033[1;31merro:\033[0m %d.%d-%d:  ",
             yylloc.first_line, yylloc.first_column, yylloc.last_column);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}

int main(int argc, char* argv[]) {
  yylineno = 0;
  return yyparse();
}
