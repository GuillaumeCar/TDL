%{
    #include "symboles.h"
	#include "calc.tab.h"
%}

%%
0|([1-9][0-9]*)                 { yylval.iVal = atoi(yytext); return NBR; };
(0|([1-9][0-9]*))*[.,][0-9]+    { yylval.dVal = atof(yytext); return FLO; };
[a-zA-Z][a-zA-Z0-9]*            { 
                                if ((yylval.symb = lookUpSymbol(yytext)) == SYMBOL_NULL)
                                    yylval.symb = installSymbol(yytext, UNDEF);
                                return (yylval.symb)->type; 
                                };
"+"                             return ADD;
"*"                             return MUL;
"/"                             return DIV;
"-"                             return SUB;
"="                             return AFF;
"\n"                            return RC;
"=="				            return EQ;
"!="				            return NEQ;
"&&"				            return AND;
"||"				            return OR;
.                               ;
%%
