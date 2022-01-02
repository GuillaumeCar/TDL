%{
#include "hoc.h"
#include "hoc.tab.h"
extern int LineNo;
%}

%%
[ \t]                  ;
[0-9]+		{yylval.Value = atof(yytext); return NUMBER; }
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
"#"		return POW;
. 		{return yytext[0]; }
%%