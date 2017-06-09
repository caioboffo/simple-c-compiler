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
#include "ast.hpp"

}

%code top {

#include <iostream>
  
extern int yylex(void);
extern int yylineno;
extern FILE *yyin;
extern char *filename;
extern bool any_errors;
 
void yyerror(char const *, ...);

void yyusage() {
  std::cout
        <<  "cmm: fatal error: no input files\n"
        <<  "compilation terminated."
        << std::endl;
}

#include "abstract_syntax_tree.hpp"
 
abstract_syntax_tree *root;
 
}

%locations

%union {
  int                               num;
  char                             *str;
  std::list<tree_node*>            *node_list;
  tree_node                        *node;
  abstract_syntax_tree             *prog;
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
%right ':'
%right '?' 
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

%type <node_list> declaration_stmt_list var_spec_list

%type <node> declaration_stmt
             var_dec
             var_spec
             var
             literal
             literal_list
             initializer
             assign
             exp

%type <num> type_specifier INT BOOL STRING


%%

program : declaration_stmt_list
        {
          $$ = new abstract_syntax_tree($1);
          root = $$;
        };

declaration_stmt_list
        : declaration_stmt_list declaration_stmt
        {
          $$ = $1;
          $1->push_back($2);
        }
        | %empty { $$ = new std::list<tree_node*>(); }
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
        : INT    { $$ = 10; }
        | BOOL   { $$ = 20; }
        | STRING { $$ = 30; }
        ;

var_spec_list
        : var_spec_list ',' var_spec
        {
          $$ = $1;
          $1->push_back($3);
        }
        | var_spec
        {
          $$ = new std::list<tree_node*>({$1});
        }
        ;
        
var_spec
        : var                 { $$ = $1; } 
        | var '=' initializer 
        {
          $$ = new identifier($1, $3);
        } 
        ;

initializer
        : exp
        | assign
        | '{' literal_list '}' { $$ = $2; }
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
*/        
literal_list
        : literal_list ',' literal
        | literal
        ;
        
/*
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

*/

assign  : var '=' exp  
        | var "+=" exp
        | var "-=" exp
        | var "*=" exp
        | var "/=" exp
        | var "%=" exp
        ;
        
var     : IDENTIFIER  { $$ = new identifier($1); }
        | IDENTIFIER '[' exp ']'  { $$ = new identifier($1, $3); } 
        ;

literal : CONSTANT       { $$ = new number($1); }
        | STRING_LITERAL { $$ = new string_literal($1); }
        | TRUE           { $$ = new boolean(1); }
        | FALSE          { $$ = new boolean(0); }
        ;

exp
        : exp '+' exp         { $$ = new plus_operation($1, $3);              }
        | exp '-' exp         { $$ = new minus_operation($1, $3);             }
        | exp '*' exp         { $$ = new times_operation($1, $3);             }
        | exp '/' exp         { $$ = new over_operation($1, $3);              }
        | exp '%' exp         { $$ = new module_operation($1, $3);            }
        | exp "<" exp         { $$ = new less_operation($1, $3);              }
        | exp ">" exp         { $$ = new greater_operation($1, $3);           }
        | exp "<=" exp        { $$ = new less_or_equal_operation($1, $3);     }
        | exp ">=" exp        { $$ = new greater_or_equal_operation($1, $3);  }
        | exp "&&" exp        { $$ = new and_operation($1, $3);               }
        | exp "||" exp        { $$ = new or_operation($1, $3);                }
        | exp "==" exp        { $$ = new equal_operation($1, $3);             }
        | exp "!=" exp        { $$ = new not_equal_operation($1, $3);         }
        | '!' exp %prec NOT   { $$ = new unary_not_operation($2);             }
        | '-' exp %prec NEG   { $$ = new unary_minus_operation($2);           }
        | exp '?' exp ':' exp
        {
          $$ = new ternary_if_operation($1, $3, $5);
        }
        | var
        | literal
          //       | subprogram_call 
        | '(' exp ')' { $$ = $2; }
        ;

%%

void yyerror(char const *s, ...) {
  if (!any_errors)
    any_errors = true;
  va_list ap;
  va_start(ap, s);

  if (yylloc.first_line)
     fprintf(stderr, "%s:%d:%d-%d: \033[1;31merror:\033[0m ",
             filename,
             yylloc.first_line,
             yylloc.first_column,
             yylloc.last_column);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}

void yyevaluate() {
  root->evaluate();
}
