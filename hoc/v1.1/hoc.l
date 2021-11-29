/**
 * 	\file 		hoc.l
 * 	\version	1.0
 * 	\date 		28 Novembre 2021
 * 	\author		Lacaes Paul
 */

%{
#define _HOC_L_
#include "hoc.h"
int installIntSymbol() ;
int installDoubleSymbol() ;
%}
    
entier 	0|([1-9][0-9]*)
reel    [0-9]*\.[0-9]+
ident   [a-zA-Z][a-zA-Z0-9_]*
%%
{entier}    {return installIntSymbol();};
{reel}      {return installDoubleSymbol();};
{ident}     { if ((yylval.symb=lookUpSymbol(yytext)) == SYMBOL_NULL)
                yylval.symb=installSymbol(yytext, VAR, UNDEF, 0, NULL);
            return (yylval.symb)->type;};
"+" 		{return ADD;};
"-" 		{return SUB;};
"*"         {return MUL;};
"/"         {return DIV;};
"="         {return AFF;};
"!"         {return NOT;};
"||"        {return OR;};
"&&"        {return AND;};
"=="        {return EGAL;};
"!="        {return DIF;};
"<"         {return INF;};
"<="        {return INFEG;};
">"         {return SUP;};
">="        {return SUPEG;};
"("         {return PO;};
")"         {return PF;};
"\n"        return RC;
.			;
%%

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
	return (yylval.symb)->type;
}