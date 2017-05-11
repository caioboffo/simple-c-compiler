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

void yyerror(char const *, ...);
  
%}

%{

int yycolumn = 1;
 
#define YY_USER_ACTION                              \
   yylloc.first_line = yylloc.last_line = yylineno; \
   yylloc.first_column = yycolumn;                  \
   yylloc.last_column = yycolumn+yyleng-1;          \
   yycolumn += yyleng;                              
   
int  comment_nesting;
 
%}

%option noyywrap yylineno

ichar [A-Za-z_]
digit [0-9]
integer {digit}+
identifier {ichar}({digit}|{ichar})*
whitespace [ \t\v\f]+
float ([+-]?{digit}+)?\.{digit}*([E|e]?[+-]?{digit}+)?

%x string
%x comment

%%

"/*"              { BEGIN(comment); ++comment_nesting;           }
<comment>[^*/\n]* { /* match non-comment delimiters */           }
<comment>\n       { yycolumn = 1;                                }
<comment>"/*"     { ++comment_nesting;                           }
<comment>"*/"     { if (--comment_nesting == 0) BEGIN(INITIAL);  }
<comment>[*/]     { /* match a / or * */                         }
<comment><<EOF>>  { yyerror("UNTERMINATED_COMMENT\n");
                    BEGIN(INITIAL); }

"//"[^\n]*        { /* single-line comments */                   }

\"                { BEGIN string;                                }
<string>[^\n\\"]+ { yymore();                                    }
<string>\n        { yyerror("MISSING_TERMINATING_STRING\n");  
                    BEGIN(INITIAL); }
<string><<EOF>>   { yyerror("MISSING_TERMINATING_STRING\n");
                    BEGIN(INITIAL); }
<string>\"        { yytext[yyleng-1] = '\0';
                    yylval.sval = strdup(yytext); BEGIN INITIAL;
                    return STRING_LITERAL; }

[\[\]\{\}\(\)\.;,:?%!=\+\-\*\/] { return *yytext; }
\n      { yycolumn = 1;             }
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

{integer}        { yylval.ival = atoi(yytext);   return CONSTANT;   } 
{identifier}     { yylval.sval = strdup(yytext); return IDENTIFIER; }

{whitespace}     { /* ignore whitespace */         }

.        { std::cout << "UNKNOWN TOKEN: " << yytext << std::endl;   }

<<EOF>>  { yypop_buffer_state();
           /* Make sure we stop if the EOF is the original input. */
           if (!YY_CURRENT_BUFFER) { yyterminate(); }
         }

%%



