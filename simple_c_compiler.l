/*
 * 
 * Copyright 2017 Caio Boffo Silva <caioboffo@gmail.com>
 * 
 * Scanner for simple-c-language-compiler.
 * 
 */
%{

#include <iostream>
#include <string>
#include "locations.hpp"
#include "error_manager.hpp"
#include "parser.hpp"
#include "symbol_table.hpp"

extern abstract_syntax_tree *syntax_tree;
extern void yyerror(char const *, ...);
extern FILE *yyin;

%}

%{

int yycolumn = 0, comment_nesting;

#define YY_BUF_SIZE 16384
 
#define YY_USER_ACTION                               \
    yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn;                  \
    yylloc.last_column = yycolumn+yyleng-1;          \
    yycolumn += yyleng;                              \

%}

%option noyywrap yylineno

ichar [A-Za-z_]
digit [0-9]
integer {digit}+
identifier {ichar}({digit}|{ichar})*
whitespace [ \t\v\f]+
float ([+-]?{digit}+)?\.{digit}*([E|e]?[+-]?{digit}+)?

%x comment

%%

"/*"              { BEGIN(comment); ++comment_nesting;           }
<comment>[^*/\n]* { /* match non-comment delimiters */           }
<comment>\n       { yycolumn = 0;                                }
<comment>"/*"     { ++comment_nesting;                           }
<comment>"*/"     { if (--comment_nesting == 0) BEGIN(INITIAL);  }
<comment>[*/]     { /* match a / or * */                         }
<comment><<EOF>>  {
                    error_manager::error("unterminated comment",  yylloc);
                    yyterminate();
                  }

"//"[^\n]*        { /* single-line comments */                   }

\"(\\.|[^"\n])*\" { 
                    yylval.str = strdup(yytext);
                    return STRING_LITERAL;
                  }

\"(\\.|[^"\n])*   { 
                    error_manager::error("missing closing quotes", yylloc);
                  }




[\[\]\{\}\(\)\.;,:?%!=\+\-\*\/] { return *yytext; }
\n      { yycolumn = 0;             }
"+="    { return PLUS_ASSIGN;       }
"-="    { return MINUS_ASSIGN;      }
"*="    { return TIMES_ASSIGN;      }
"/="    { return OVER_ASSIGN;       }
"%="    { return MOD_ASSIGN;        }
"<"     { return LT;                }
"<="    { return LE;                }
">"     { return GT;                }
">="    { return GE;                }
"=="    { return EQ;                }
"!="    { return NE;                }
"&&"    { return AND;               }
"||"    { return OR;                }

"bool"   { return BOOL;             }
"string" { return STRING;           }
"int"    { return INT;              }
true     { return TRUE;             }
false    { return FALSE;            }

if       { return IF;               }
else     { return ELSE;             }
while    { return WHILE;            }
for      { return FOR;              }
break    { return BREAK;            }
return   { return RETURN;           }
read     { return READ;             }
write    { return WRITE;            }

{integer}        { yylval.num = atoi(yytext);   return CONSTANT;   } 
{identifier}     { 
                   symbol_table::insert(yytext);
                   yylval.str = strdup(yytext); 
                   return IDENTIFIER; 
                 }

{whitespace}     { /* ignore whitespace */         }

.        { error_manager::error("unkonw token", yylloc); }

<<EOF>>  { 
           yypop_buffer_state();
           
           if (!YY_CURRENT_BUFFER) { yyterminate(); }
         }

%%

#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/Support/raw_ostream.h>

int main(int argc, char* argv[]) {
  FILE *fh;
  
  if (argc == 2 && (fh = fopen(argv[1], "r"))) {
    error_manager::filename = argv[1];
    yyin = fh;
    if (!yyin)
      yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));
  } else {
    std::cout
      <<  "cmm: fatal error: no input files\n"
      <<  "compilation terminated."
      << std::endl;

    exit(EXIT_FAILURE);
  }

  yylineno = 1;

  symbol_table::create_symbol_table();

  yyparse();

  if (!error_manager::had_error()) {
    syntax_tree->evaluate();

    if (!symbol_table::lookup("main")) 
      error_manager::error("undefined reference to main", yylloc);

    symbol_table::delete_symbol_table();
    
    if (!error_manager::had_error()) {
      symbol_table::create_symbol_table();
      syntax_tree->emit_ir_code();
      // print llvm ir to standard output
      llvm::legacy::PassManager PM;
      PM.add(llvm::createPrintModulePass(llvm::outs()));
      PM.run(*(syntax_tree->module));
    }
  }

  fclose(fh);
  
  exit(EXIT_SUCCESS);
}


