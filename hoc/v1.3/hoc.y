/**
 *	\file		hoc.y
 *	\version	1.2
 *	\date		26 Janvier 2021
 *	\author		Samir El Khattabi
*/
%{
#define _HOC_Y_
#include "hoc.h"
extern int yylex(void);
void init(void);
int isFloat = 0;
%}
/* YYSTYPE  : Définition des valeurs sémantiques (yylval renseignée par lex) */
%union {
	int			entier;
	double		reel;
	pSymbol_t	symb;
}
/* Tokens fictifs : déclaration des classes */
%token DAT CST VAR PRG
%token RC
/* Tokens nombres */
%token	<symb> ENTIER REEL
/* Token pour identifiant non reconnu */
%token	<symb> UNDEF
/* Tokens pour les variables : passage de UNDEF vers IVAR/FVAR */
%token	<symb> IVAR FVAR
/* Token pour fonction prédéfinie */
%token	<symb> PREDEF
%token <symb> ADD SUB MUL DIV
%token <symb> PO PF
%token AFF
%token PR_TS DBG_TS

/* Typage des unités syntaxiques */
%type <reel> expr assgn
%type <symb> opAlg

/* Associativités & priorités */
%right AFF
%left ADD SUB
%left MUL DIV
%nonassoc UNARY_MINUS

%%
liste :	/* VIDE */
	| liste RC 			{ init (); }
	| liste expr  RC	{ printExpr(isFloat,$2); init (); }
	| liste assgn RC    { printExpr(isFloat,$2); init (); }
	| liste error RC    { yyerrok; yyclearin; init ();}
	| liste cmd RC 		{ init(); }
	;

cmd: PR_TS 		{ printSymbolList(); }
	| DBG_TS 	{ /*dbgSymbolList(); */}
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

opAlg: ADD | SUB | MUL | DIV;

expr :	ENTIER 			{ $$=*(int *)$1->U.pValue; }
    | REEL 				{ memcpy((generic)&$$, $1->U.pValue, $1->size); isFloat=1;}
	| IVAR  			{ $$=*(int *)$1->U.pValue; }
	| FVAR   			{ memcpy((generic)&$$, $1->U.pValue, $1->size); isFloat=1;}
	| UNDEF				{ yyerror("Variable  <%s> indéfinie", $1->name); YYERROR;}
	| PO expr PF  		{ $$=$2; }
	| expr opAlg expr	{ $$ = (*($2->U.pFct))($1, $3); }
	| SUB expr 			{ $$ = -$2; } %prec UNARY_MINUS
	| PREDEF PO expr PF { $$ = (*($1->U.pFct))($3); isFloat=1;}
	;
%%

/**
 *	\var        progName
 *	\brief		Nom du programme
 *	\note 		A déclarer avec l'attribut "extern" par les utilisateurs
 */
char * progName;
int main(int argc, char **argv) {
    int resParse;
    
	progName = argv[0];
	printMessage(0);
	printMessage(1);
    installDefaultSymbols();
    init();
	//    while ((resParse=yyparse())!=0) init();
    resParse=yyparse();
	printMessage(2);
    return 0;
}
void init(void) {
	prompt();
    isFloat = 0;
}

