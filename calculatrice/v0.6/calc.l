%{
#include <stdlib.h>
#include "calc.tab.h"
%}

%%
0|([1-9][0-9]*)		    { yylval.iVal = atoi(yytext);return NBR; };
"+"				        return ADD;
"-"				        return SUB;
"="                     return AFF;
([0-9]*[.])?[0-9]+      { yylval.dVal = atof(yytext);return FLT; };
\n 				        return RC;
[a-z]                   { yylval.iVal = yytext[0]-'a'; return ACCI; }
[A-Z]                   { yylval.iVal = yytext[0]-'A'; return ACCD; }
quit			        return 0;
. 				        ;
%% 