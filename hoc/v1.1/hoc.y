/**
 * 	\file 		hoc.y
 * 	\version	1.0
 * 	\date 		28 Novembre 2021
 * 	\author		Lacaes Paul
 */

%{
    #define _HOC_Y_
    #include "hoc.h"
    extern int yylex(void);
    void yyerror(char *s);
    int isFloat = 0;
    void init(void) { isFloat = 0; printf("hoc>");}
%}

%union {
        int entier;
        double reel;
        pSymbol_t symb;
}
/* Tokens sans valeur sémantiques */
%token ADD SUB MUL DIV AFF RC NOT OR AND EGAL DIF INF INFEG SUP SUPEG PO PF PRG
/* Tokens fictifs : déclaration des classes */
%token DAT CST VAR
/* Tokens nombres */
%token <symb> ENTIER REEL PREDEF
/* Token pour identifiant non reconnu */
%token <symb> UNDEF
/* Tokens pour les variables : passage de UNDEF vers IVAR/FVAR */
%token <symb> IVAR FVAR



/* Typage des unités syntaxiques */
%type <reel> expr valeur assgn

%right AFF OR AND EGAL DIF INF INFEG SUP SUPEG
%left ADD SUB NOT
%left MUL DIV
%nonassoc UMINUS


%start list

%%
list    : /* VIDE */
        | list expr RC          {
                                        if (isFloat) printf("= %lf\n", $2); 
                                        else printf("= %d\n", (int)$2);
                                        init();
                                }
        | list assgn RC         {
                                        if (isFloat) printf("= %lf\n", $2); 
                                        else printf("= %d\n", (int)$2);
                                        init();
                                }
        | list error RC         { 
                                        yyerror("Error");
                                        yyerrok;
                                        init();
                                }
        | list RC               {init();}
        ;
expr    : expr ADD expr         { $$ = $1 + $3;}
        | expr SUB expr         { $$ = $1 - $3;}
        | expr MUL expr         { $$ = $1 * $3;}
        | expr DIV expr         {
                                        if ($3!= 0) {
                                                $$ = $1 / $3;
                                        }else { 
                                                yyerror("Division par 0");YYERROR;
                                }}
        | SUB expr              { $$ = -$2;} %prec UMINUS
        | PO expr PF            { $$ = $2; }
        | NOT expr              { $$ = !$2;}
        | expr OR expr          { $$ = $1 || $3;}
        | expr AND expr         { $$ = $1 && $3;}
        | expr EGAL expr        { $$ = $1 == $3;}
        | expr DIF expr         { $$ = $1 != $3;}
        | expr INF expr         { $$ = $1 < $3;}
        | expr INFEG expr       { $$ = $1 <= $3;}
        | expr SUP expr         { $$ = $1 > $3;}
        | expr SUPEG expr       { $$ = $1 >= $3;}
        | PREDEF PO expr PF     { $$ = ( *($1->U.pFct) ) ($3); isFloat=1;}
        | valeur
        ;
valeur  : ENTIER                { $$= *(int *) $1->U.pValue; }
        | REEL                  { $$= *(double *) $1->U.pValue;isFloat=1; }
        | IVAR                  { $$= *(int *) $1->U.pValue; }
        | FVAR                  { $$= *(double *) $1->U.pValue; isFloat = 1; }
        | UNDEF                 { yyerror("Variable indéfinie");YYERROR; }
        ;
assgn   : IVAR AFF expr         { $$ = *(int *) $1->U.pValue = $3; }
        | FVAR AFF expr         { $$ = *(double *) $1->U.pValue = $3; isFloat=1; }
        | UNDEF AFF expr        { 
                                        $1->clas = VAR; 
                                        $1->type= (isFloat) ? FVAR : IVAR ; 
                                        $1->size = (isFloat) ? sizeof(double) : sizeof(int) ;
                                        if (isFloat) { 
                                                $1->U.pValue = (double*) malloc (sizeof(double)); 
                                                $$ = *(double *) $1->U.pValue = $3;
                                        } else {
                                                $1->U.pValue= (int*) malloc(sizeof(int)); 
                                                $$ = *(int *) $1->U.pValue = $3;
                                }}
        ;
%%

void yyerror(char *s){
    printf("%s\n", s);
}

int main(){
        installDefaultSymbols();
        init();
        yyparse();
        return 0;
        
}
