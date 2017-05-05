/*
 * 
 * Copyright 2017 Caio Boffo Silva <caioboffo@gmail.com>
 * 
 * Scanner for simple-c-language-compiler.
 * 
 */
%{

#include <stdio.h>
#include <string.h>
#include "parser.hpp"

int  comment_nesting;
 
%}

%option noyywrap

ichar [A-Za-z_]
digit [0-9]
integer {digit}+
identifier {ichar}({digit}|{ichar})*
whitespace [ \t\n\v\f]+
float ([+-]?{digit}+)?\.{digit}*([E|e]?[+-]?{digit}+)?

%x string
%x comment

%%

"/*"              { BEGIN(comment); ++comment_nesting;           }
<comment>[^*/]*   { /* match non-comment delimiters */           }
<comment>"/*"     { ++comment_nesting;                           }
<comment>"*/"     { if (--comment_nesting == 0) BEGIN(INITIAL);  }
<comment>[*/]     { /* match a / or * */                         }
<comment><<EOF>>  { printf("UNTERMINATED_COMMENT");
                    BEGIN(INITIAL); }

"//"[^\n]*        { /* single-line comments */                   }

\"                { BEGIN string;                                }
<string>[^\n\\"]+ { yymore();                                    }
<string>\n        { printf("MISSING_TERMINATING_STRING\n");      }
<string><<EOF>>   { printf("MISSING_TERMINATING_STRING\n");
                    BEGIN(INITIAL); }
<string>\"        { yytext[yyleng-1] = '\0';
                    yylval.sval = strdup(yytext); BEGIN INITIAL;
                    return STRING_LITERAL; }

[\[\]\{\}\(\)\.;,:?%!=\+\-\*\/] { return *yytext; }

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
"void"   { return VOID;             }
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

.        { printf("UNKNOWN TOKEN: %s\n", yytext);  }


%%



