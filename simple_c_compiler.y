/*
 * 
 * Copyright 2017 Caio Boffo Silva <caioboffo@gmail.com>
 * 
 * Parser for simple-c-language-compiler.
 * 
 */

%code requires {

#include <string>
#include <fstream>
#include <cstdlib>
#include <cstdarg>
#include <list>
#include "identifier.hpp"
#include "statement.hpp"
#include "expression.hpp"
#include "program.hpp"
#include "variable_declaration.hpp"

}

%code top {

#include <iostream>
  
extern int yylex(void);
extern int yylineno;
void yyerror(char const *, ...); 

void usage() {
  std::cout
        <<  "cmm: fatal error: no input files\n"
        <<  "compilation terminated."
        << std::endl;
}

#include "program.hpp"
 
program *root;
 
}

%locations

%union {
  int                               num;
  char                             *str;
  std::list<statement*>            *stmt_list;
  statement                        *stmt;
  program                          *prog;
  expression                       *exp;
  std::list<expression*>           *exp_list;
}

%token <num> CONSTANT
%token <str> STRING_LITERAL
%token <str> IDENTIFIER

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
%left ':'
%left '?' 
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

%type <prog> program
%type <stmt_list> declaration_stmt_list
%type <stmt> declaration_stmt var_dec
%type <exp> var var_spec
%type <exp_list> var_spec_list
%type <num> type_specifier INT BOOL STRING

%%

program : declaration_stmt_list { $$ = new program($1); root = $$; }

declaration_stmt_list
        : declaration_stmt_list declaration_stmt
        {
          $$ = $1;
          $1->push_back($2);
        }
        | %empty { $$ = new std::list<statement*>(); }
        ;

declaration_stmt 
        : var_dec
        ;

var_dec : type_specifier var_spec_list ';'
        {
          $$ = new variable_declaration($1, $2); 
        }
        ;

type_specifier
        : INT
        | BOOL
        | STRING ;

var_spec_list
        : var_spec ',' var_spec_list
        {
          $$ = $3;
          $3->push_back($1);
        }
        | var_spec
        {
          $$ = new std::list<expression*>({$1});
        }
        ;
        
var_spec
        : var
        /* | var '=' initializer */
        ;
     

/*
declaration_stmt
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

initializer
        : exp
        | assign
        | '{' literal_list '}'
        ;
        
literal_list
        : literal ',' literal_list
        | literal
        ;
        

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
        | BREAK ';'  
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
*/
        
var     : IDENTIFIER  { $$ = new identifier($1); }
/*        | IDENTIFIER '[' exp ']'  { $$ = new identifier($1); } */
        ;
/*
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
*/
%%

void yyerror(char const *s, ...) {
  va_list ap;
  va_start(ap, s);

  if (yylloc.first_line)
     fprintf(stderr, "arquivo.cpp:%d:%d: \033[1;31merror:\033[0m ",
             yylloc.first_line,
             yylloc.first_column);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}

main(int argc, char* argv[]) {
  yylineno = 1;
  yyparse();
  root->evaluate();
}
