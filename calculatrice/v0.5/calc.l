%{
#include <stdlib.h>
#include "calc.tab.h"
%}

%%
0|([1-9][0-9]*)		{ yylval = atoi(yytext);return NBR; };
"+"				return ADD;
"-"				return SUB;
"="             return AFF;
\n 				return RC;
[a-z]           { yylval = yytext[0]-'a'; return ACC; }
quit			return 0;
. 				;
%% 