/**
 *	\file		hoc.y
 *	\version	1.1
 *	\date		26 Janvier 2021
 *	\author		Samir El Khattabi
 */
%{
#define _HOC_Y_
#include "hoc.h"
void yyerror(char *strErr);
extern int yylex(void);
void init(void);
void printExpr(double val);
int isFloat = 0;	/* Expression entière ou réelle*/
%}
/* YYSTYPE  : Définition des valeurs sémantiques (yylval renseignée par lex) */
%union {
	int			entier;
	double		reel;
	pSymbol_t	symb;
}
/* Tokens fictifs : déclaration des classes */
%token DAT CST VAR PRG
/* Tokens nombres */
%token	<symb> ENTIER REEL
/* Token pour identifiant non reconnu */
%token	<symb> UNDEF
/* Tokens pour les variables : passage de UNDEF vers IVAR/FVAR */
%token	<symb> IVAR FVAR
/* Token pour fonction prédéfinie */
%token	<symb> PREDEF
/* Typage des unités syntaxiques */
%type	<reel> expr assgn
%token RC
%token PO PF
%token ADD SUB MUL DIV
%token AFF
/* Associativités & priorités */
%right AFF
%left ADD SUB
%left MUL DIV
%nonassoc UNARY_MINUS

%%
liste :	/* VIDE */
	| liste RC 			{ init (); }
	| liste expr  RC	{ printExpr($2); init (); }
	| liste assgn RC    { printExpr($2); init (); }
	| liste error RC    { yyerrok; yyclearin; init ();}
	;

assgn :
      IVAR AFF expr		{ $$ = *(int *)$1->U.pValue    = $3; }
	| FVAR  AFF expr    { $$ = *(double *)$1->U.pValue = $3; }
	| UNDEF AFF expr    {
        $1->clas = VAR;
        $1->type = (isFloat)?FVAR:IVAR;
        $1->size = (isFloat)?sizeof(double):sizeof(int);
       	if (isFloat) {
            $1->U.pValue=(double*)malloc(sizeof(double));
            $$ = *(double *)$1->U.pValue = $3;
     	} else {
            $1->U.pValue=(int*)malloc(sizeof(int));
            $$ = *(int *)$1->U.pValue = $3;
        }
    }
	;
expr :	ENTIER 			{ $$=*(int *)$1->U.pValue; }
    | REEL 				{ memcpy((generic)&$$, $1->U.pValue, $1->size); isFloat=1;}
	| IVAR  			{ $$=*(int *)$1->U.pValue; }
	| FVAR   			{ memcpy((generic)&$$, $1->U.pValue, $1->size); isFloat=1;}
	| PO expr PF  		{ $$=$2; }
	| expr ADD expr 	{ $$ = $1+$3; }
	| expr SUB expr 	{ $$ = $1-$3; }
	| expr MUL expr 	{ $$ = $1*$3; }
	| expr DIV expr
		{ if ($3 == 0) {
            yyerror("ERREUR ARITH : Div par 0");
            YYERROR;
             }
  			else $$ = $1/$3;
		}
	| SUB expr 			{ $$ = -$2; } %prec UNARY_MINUS
	| PREDEF PO expr PF { $$ = (*($1->U.pFct))($3); isFloat=1;}
	;
%%

int main(int argc, char **argv) {
    int resParse;
    
    installDefaultSymbols();
    init();
//    while ((resParse=yyparse())!=0) init();
    resParse=yyparse();
    printf("Le parseur se termine dans l'état %d\n", resParse);
    return 0;
}
void yyerror(char *strErr) {
    printf ("!%s!\n",strErr);
}
void init(void) {
    printf("hoc > ");
    isFloat = 0;
}
void printExpr(double val) {
    if (isFloat) printf("\033[42;37m= [%lf]\033[0m\n", val);
    else printf("\033[44;37m= [%d]\033[0m\n", (int)val);
}

