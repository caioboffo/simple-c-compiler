/*
 * Copyright 2017 Caio Boffo Silva <caioboffo@gmail.com>
 * 
 * Scanner for simple-c-language-compiler.
 * 
 */

%{
  #define MAX_STR_SIZE 4294967291
  #include <stdio.h>
  #include <string.h>
  int comment_nesting, bc;
  char string_buffer[MAX_STR_SIZE];
  char *string_buffer_ptr;
%}

ID  [A-Za-z_][A-Za-z0-9_]*
/* EXP ([Ee][+-]?[0-9]+)
   NUM ([0-9]+|[0-9]*"."[0-9]+{EXP}?) */
NUM [0-9]+

%x STRING
%x COMMENT

%%

"/*"             BEGIN(COMMENT); ++comment_nesting;
<COMMENT>[^*/]*  /* match non-comment delimiters */
<COMMENT>"/*"    ++comment_nesting;
<COMMENT>"*/"    if (--comment_nesting == 0) BEGIN(INITIAL);
<COMMENT>[*/]    /* match a / or * */
<COMMENT><<EOF>> printf("UNTERMINATED_COMMENT"); 

\" {
  bc = 0;
  memset(string_buffer, 0, MAX_STR_SIZE);
  string_buffer_ptr = string_buffer;
  BEGIN(STRING);
}
<STRING>\" { /* closing quote */
  BEGIN(INITIAL);
  *string_buffer_ptr = '\0';
  /* return string constant tokent type and value to parser */
  strcpy(yytext, string_buffer);
  printf("%s\n", yytext);
}
<STRING>\n {
  /* unterminated string constant */
  printf("MISSING_TERMINATING_STRING\n");
 }
<STRING>\\n *string_buffer_ptr++  = '\n';
<STRING>\\t *string_buffer_ptr++  = '\t';
<STRING>[^\\\n\"]+ { /* any character except \\\n\" */
  char *yptr = yytext;
  while (*yptr) {
    *string_buffer_ptr++ = *yptr++;
  }
}
<STRING><<EOF>> printf("MISSING_TERMINATING_STRING\n");

"+"     { printf("+\n");                 }
"-"     { printf("-\n");                 }
"*"     { printf("*\n");                 }
"/"     { printf("/\n");                 }
"="     { printf("=\n");                 }
"!"     { printf("!");                   }
"+="    { printf("+=\n");                }
"-="    { printf("-=\n");                }
"*="    { printf("*=\n");                }
"/="    { printf("/=\n");                }
"%="    { printf("\%=\n");               }
"<"     { printf("<\n");                 }
"<="    { printf("<=\n");                }
">"     { printf(">\n");                 }
">="    { printf(">=\n");                }
"=="    { printf("==\n");                }
"!="    { printf("!=\n");                }
"&&"    { printf("&&\n");                }
"||"    { printf("||\n");                }

"?"     { printf("?\n");                 }
":"     { printf(":\n");                 }
"["     { printf("[\n");                 }
"]"     { printf("]\n");                 }
"{"     { printf("{\n");                 }
"}"     { printf("}\n");                 }
"("     { printf("(\n");                 }
")"     { printf(")\n");                 }
"."     { printf(".\n");                 }
";"     { printf(";\n");                 }
","     { printf(",\n");                 }


[ \t\n] { /* ignore whitespaces */       }

"bool"   { printf("IF\n");                }
"string" { printf("STRING\n");            }
"int"    { printf("INTEGER\n");           }
"void"   { printf("VOID\n");              }
true   { printf("TRUE\n");              }
false  { printf("FALSE\n");             }

if     { printf("IF\n");                }
else   { printf("ELSE\n");              }
while  { printf("WHILE\n");             }
for    { printf("FOR\n");               }
break  { printf("IF\n");                }
return { printf("RETURN\n");            }
read   { printf("READ\n");              }
write  { printf("WRITE\n");             }

{NUM}   { printf("NUMBER %s\n", yytext); }
{ID}    { printf("ID %s\n", yytext);     }

.      { printf("UNKNOWN SYMBOL: %s\n", yytext); }


%%

int main(int argc, char *argv[])
{
  yylex();
  return 0;
}

