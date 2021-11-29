%{
#include "hoc.h"
#include "hoc.tab.h"
extern int LineNo;
%}

%%
[ \t]                  ;
[0-9]+		{ yylval.Symb = Install("", NUM,atof(yytext),"(double *)");  return NUM; };
"quit"		return 0;
[a-z][a-z0-9]* {Symbol *Sp;
		   if ((Sp = LookUp(yytext)) == 0)
			Sp = Install(yytext, UNDEF, 0.0, yytext);
		   yylval.Symb = Sp;
		   return Sp->Type == UNDEF ? VAR : Sp->Type;}
\n		{LineNo++; return RC; }
"+"		return ADD;
"-"		return SUB;
"*"		return MUL;
"/"		return DIV;
"#"		return POW;
"("		return OP;
")"		return CP;
"!"		return NOT;
"&&"    return AND;
"||"    return OR;
"=="    return EQU;
"!="    return NOTEQU;
"<"     return INF;
">"     return SUP;
"<="    return INFEQU;
">="    return SUPEQU;
"="		return ASSIGN;
"?"		return PRINT;
"@"		return DEBUG;
"IF"    return IF;
"ELSE"  return ELSE;
";"     return SEMICOLON;
. 		{return yytext[0]; }
%%