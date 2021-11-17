%{
#include <stdlib.h>
#include "calc.tab.h"
%}

%%
0|([1-9][0-9]*)		{yylval = atoi(yytext);return NUM;};
"+"				return ADD;
"-"				return SUB;
"*"				return MUL;
"/"				return DIV;
"="				return AFF;
[a-z]			{yylval = yytext[0] - 'a';return REG;}
[A-Z]			{yylval = yytext[0] - 'A';return REG;}
\n 				return RC;
quit			return 0;
[ \t]			;
. 				return yytext[0];
%% 