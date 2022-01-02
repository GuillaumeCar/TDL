%{
	#include "expr.h"
	#include "y.tab.h"
	extern int lineNo;
%}

%%
[ \t]	;
(quit|exit|ciao|bye)			{return 0;};
"PRINT"	return PRINT;
[0-9]+\.?|[0-9]*\.[0-9]+	{
		printf("number\n");
		yylval.symbol = installSymbol("", NUMBER, atof(yytext));
		return NUMBER;
	}
[a-zA-Z][a-zA-Z0-9]*	{
		printf("not number\n");
		Psymbol sp = lookUpSymbol(yytext);
		if(sp==SYMB_NULL) sp=installSymbol(yytext, UNDEF, 0.0);
		yylval.symbol = sp;
		return sp->type;
	}
\n	{
		lineNo++;
		return '\n';
	}
.								return yytext[0];
<<EOF>>					return 0;
"=="						return EQ;
"<"							return INF;
">"							return SUP;
"&&"						return LOG_AND;
"||"						return LOG_OR;
%%
