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
#include "parser.hpp"
#include "symbol_table.hpp"


extern void yyusage();
extern void yyevaluate();
extern void yyerror(char const *, ...);

 
%}

%{

int yycolumn = 0, comment_nesting;
bool any_errors;
char *filename;
symbol_table *sym_table;

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
                    yyerror("unterminated comment");
                    yyterminate();
                  }

"//"[^\n]*        { /* single-line comments */                   }

\"(\\.|[^"\n])*\" { 
                    yylval.str = strdup(yytext);
                    return STRING_LITERAL;
                  }

\"(\\.|[^"\n])*   { 
                    yyerror("missing closing quotes");
                  }




[\[\]\{\}\(\)\.;,:?%!=\+\-\*\/] { return *yytext; }
\n      { yycolumn = 0;             }
"+="    { return PLUS_ASSIGN;       }
"-="    { return MINUS_ASSIGN;      }
"*="    { return TIMES_ASSIGN;      }
"/="    { return OVER_ASSIGN;       }
"%="    { return MOD_ASSIGN;        }
"<"     { return GT;                }
"<="    { return GE;                }
">"     { return LT;                }
">="    { return LE;                }
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
                   sym_table->insert(yytext);
                   yylval.str = strdup(yytext); 
                   return IDENTIFIER; 
                 }

{whitespace}     { /* ignore whitespace */         }

.        { yyerror("unkonw token"); }

<<EOF>>  { 
           yypop_buffer_state();
           
           if (!YY_CURRENT_BUFFER) { yyterminate(); }
         }

%%

int main(int argc, char* argv[]) {
  FILE *fh;
  
  if (argc == 2 && (fh = fopen(argv[1], "r"))) {
    filename = argv[1];
    yyin = fh;
    if (!yyin)
      yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));
  } else {
    yyusage();
    exit(EXIT_FAILURE);
  }

  yylineno = 1;

  sym_table = new symbol_table();
  sym_table->insert("read");
  sym_table->insert("write");

  yyparse();
  if (!any_errors)
    yyevaluate();

  fclose(fh);
  
  exit(EXIT_SUCCESS);
}


