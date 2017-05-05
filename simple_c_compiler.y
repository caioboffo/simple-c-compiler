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

extern int yylex(void);
void yyerror(char const *); 

void usage() {
  std::cout << "simple-c-compiler: fatal error: no input files" << std::endl;
  std::cout << "compilation terminated." << std::endl;
}
 
%}

%expect 0

%union {
  int    ival;
  double dval;
  char*  sval;
}

%token <ival> CONSTANT
%token <sval> STRING_LITERAL
%token <sval> IDENTIFIER

%token IF ELSE WHILE FOR BREAK RETURN READ WRITE
       INT VOID BOOL STRING TRUE FALSE
       
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

/* Generate the parser description file.  */
%verbose
/* Enable run-time traces (yydebug).  */
%define parse.trace

%%

translation_unit
        : external_declaration
        | translation_unit external_declaration 
        ;

external_declaration
        : declaration subprogram_definition
        | subprogram_definition 
        ;

subprogram_definition
        : function_definition
        | procedure_definition
        ;

function_definition
        : declaration_specifiers declarator compound_statement
        ;

procedure_definition
        : declarator compound_statement
        ;

compound_statement
        : '{' '}'
        | '{' statement_list '}'
        | '{' declaration_list '}'
        | '{' declaration_list statement_list '}'
        ;


statement_list
        : statement
        | statement_list statement
        ;

declaration_list
        : declaration
        | declaration_list declaration
        ;

statement
        : compound_statement
        | input_output_statement
        | expression_statement
        | selection_statement
        | iteration_statement
        | jump_statement
        ;

input_output_statement
        : READ IDENTIFIER ';'
        | WRITE argument_expression_list ';'
        ;

expression_statement
        : ';'
        | expression ';'
        ;
        
selection_statement
        : IF '(' expression ')' statement  %prec THEN
        | IF '(' expression ')' statement ELSE statement
        ;
        
iteration_statement
        : WHILE '(' expression ')' statement
        | FOR '(' expression_statement expression_statement ')' statement
        | FOR '(' expression_statement expression_statement expression ')' statement
        ;
        
jump_statement
        : BREAK ';'
        | RETURN ';'
        | RETURN expression ';'

declaration
        : declaration_specifiers init_declarator_list ';'
        ;

declaration_specifiers
        : type_specifier
        ;

type_specifier 
        : VOID
        | BOOL
        | STRING
        | INT
        ;

init_declarator_list
        : init_declarator
        | init_declarator_list ',' init_declarator
        ;

init_declarator
        : declarator
        | declarator '=' initializer
        ;

declarator
        : direct_declarator
        ;

direct_declarator
        : IDENTIFIER
        | '(' declarator ')'
        | direct_declarator '[' constant_expression ']'
        | direct_declarator '[' ']'
        | direct_declarator '(' parameter_type_list ')'
        | direct_declarator '(' identifier_list ')'
        | direct_declarator '(' ')'
        ;

constant_expression
        : conditional_expression
        ;


parameter_type_list
        : parameter_list
        ;

parameter_list
        : parameter_declaration
        | parameter_list ',' parameter_declaration
        ;

parameter_declaration
        : declaration_specifiers declarator
        | declaration_specifiers
        ;

identifier_list
        : IDENTIFIER
        | identifier_list ',' IDENTIFIER
        ;
        

initializer
        : assignment_expression
        | '{' initializer_list '}'
        | '{' initializer_list ',' '}'
        ;

initializer_list
        : initializer
        | initializer_list ',' initializer
        ;

expression
        : assignment_expression
        | expression ',' assignment_expression
        ;
        
assignment_expression
        : conditional_expression
        | unary_expression assignment_operator assignment_expression
        ;

primary_expression
        : IDENTIFIER
        | CONSTANT
        | STRING_LITERAL
        | '(' expression ')'
        ;

postfix_expression
        : primary_expression
        | postfix_expression '[' expression ']'
        | postfix_expression '(' ')'
        | postfix_expression '(' argument_expression_list ')'
        ;

argument_expression_list
        : assignment_expression
        | argument_expression_list ',' assignment_expression
        ;


unary_operator
        : '-'
        | '!'
        ;
        
unary_expression
        : postfix_expression
        | unary_operator postfix_expression
        ;
        
multiplicative_expression
        : unary_expression
        | multiplicative_expression '*' unary_expression
        | multiplicative_expression '/' unary_expression
        | multiplicative_expression '%' unary_expression
        ;

additive_expression
        : multiplicative_expression
        | additive_expression '+' multiplicative_expression
        | additive_expression '-' multiplicative_expression
        ;
        
relational_expression
        : additive_expression
        | relational_expression "<" additive_expression
        | relational_expression ">" additive_expression
        | relational_expression "<=" additive_expression
        | relational_expression ">=" additive_expression
        ;

equality_expression
        : relational_expression
        | equality_expression "==" relational_expression
        | equality_expression "!=" relational_expression
        ;


logical_and_expression
        : equality_expression
        | logical_and_expression "&&" equality_expression
        ;

logical_or_expression
        : logical_and_expression
        | logical_or_expression "||" logical_and_expression
        ;

conditional_expression
        : logical_or_expression
        | logical_or_expression '?' expression ':' conditional_expression
        | TRUE
        | FALSE
        ;
        
assignment_operator
        : '='
        | "+=" 
        | "-="
        | "*=" 
        | "/=" 
        | "%="
        ;



%%

void yyerror (char const *s) {
  fprintf(stderr, "syntar error: %s\n", s);
}

int main(int argc, char* argv[]) {
  return yyparse();
}
