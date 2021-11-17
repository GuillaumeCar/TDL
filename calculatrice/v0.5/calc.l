%{
#include <stdlib.h>
#include "calc.tab.h"
%}

%%
0|([1-9][0-9]*)		{ yylval.iVal = atoi(yytext);return NBR; };
/* TODO: float regex */
"+"				return ADD;
"-"				return SUB;
"="             return AFF;
\n 				return RC;
[a-z]           { yylval.iVal = yytext[0]-'a'; return ACC; }
quit			return 0;
. 				;
%% 