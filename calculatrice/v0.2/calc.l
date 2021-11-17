%{
#include <stdlib.h>
#include "calc.tab.h"
%}

%%
0|([1-9][0-9]*)		{yylval = atoi(yytext);return NBR;};
"+"				return ADD;
"-"				return SUB;
\n 				return RC;
quit			return 0;
[ \t]			;
. 				return yytext[0];
%% 