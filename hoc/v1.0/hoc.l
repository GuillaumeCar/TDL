%{
#include "hoc.tab.h"

int installIntSymbol() {
	int *pValue = (int *)malloc (sizeof(int));
	*pValue = atoi(yytext);
	yylval.symb = installSymbol("", DAT, ENTIER, sizeof(int), pValue);
	return (yylval.symb)->type;
}
int installDoubleSymbol() {
	double *pValue = (double *)malloc (sizeof(double));
	*pValue = atof(yytext);
	yylval.symb = installSymbol("", DAT, REEL, sizeof(double), pValue);
	return (yylval.symb)->type; }
%}

entier [0-9]+
reel (([0-9]+\.?)|([0-9]*\.[0-9]+)

%%
{entier} return installIntSymbol() ;
{reel} return installDoubleSymbol() ;
"print"     return PRINT;
"quit"		return 0;
[a-zA-Z][a-zA-Z0-9]* {Symbol *Sp;
		   if ((Sp = LookUp(yytext)) == 0)
			Sp = Install(yytext, UNDEF, 0.0);
		   yylval.Symb = Sp;
		   return Sp->Type == UNDEF ? VAR : Sp->Type;}
\n		{LineNo++; return RC; }
"+"		return ADD;
"-"		return SUB;
"*"		return MUL;
"/"		return DIV;
. 		{return yytext[0]; }
%%