%{
    #include <stdio.h>
    #include "symboles.h"
    extern int yylex(void);
    void yyerror(char *err);
    void printFloat(float token);
    int isFloat = 0;
    void init (void) {isFloat = 0; printf(" = %d", isFloat);}
%}


%union {
        int entier;
        double reel;
        pSymbol_t symb;
}

/* Tokens fictifs : déclaration des classes */
%token DAT CST VAR
/* Tokens nombres */
%token <symb> ENTIER REEL
/* Token pour identifiant non reconnu */
%token <symb> UNDEF
/* Tokens pour les variables : passage de UNDEF vers IVAR/FVAR */
%token <symb> IVAR FVAR
/* Typage des unités syntaxiques */
%type <reel> expr assgn valeur

%token ADD SUB RC AFF MUL DIV EQ NEQ AND OR

%type <symb> ident

%right AFF
%left ADD SUB
%left MUL DIV
%nonassoc UMINUS

%start list

%%
list    :   /* VIDE */
        | list expr RC      {   printFloat($2); }
        | list assgn RC    {   printFloat($2); }
        | list error RC     {   yyerror("DANGER !"); yyerrok; }
        | list RC
        ;
        
expr    : expr ADD expr { $$ = $1 + $3; }
        | expr SUB expr { $$ = $1 - $3; }
        | expr MUL expr { $$ = $1 * $3; }
        | expr EQ expr { $$ = $1 == $3; }
        | expr NEQ expr { $$ = $1 != $3; }
        | expr AND expr { $$ = $1 && $3; }
        | expr OR expr { $$ = $1 || $3; }
        | expr DIV expr { 
                                if ($3 != 0) {
                                        $$ = $1 / $3; 
                                } else {
                                        // On invoque une erreur
                                        yyerror("Division par 0");
                                        yyerrok;
                                }
                        }
        | SUB expr { $$ = -$2; } %prec UMINUS
        | valeur
        ;

valeur  : 
    ENTIER { $$ =*(int *) $1->pValue; }
    | REEL { memcpy( (generic) &$$, $1->pValue, $1->size); isFloat=1; }
    | IVAR { $$ =*(int *) $1->pValue; }
    | FVAR { $$ =*(double *) $1->pValue; isFloat=1; }
    | UNDEF { yyerror("Variable non définie !"); yyerrok; }
    ;

assgn :
    IVAR AFF expr { $$ = *(int *) $1->pValue = $3; }
    | FVAR AFF expr { $$ = *(double *) $1->pValue = $3; isFloat=1; }
    | UNDEF AFF expr {
        $1->clas = VAR;
        $1->type= (isFloat) ? FVAR : IVAR ;
        $1->size = (isFloat) ? sizeof(double) : sizeof(int) ;
        if (isFloat) {
            $1->pValue = (double*) malloc (sizeof(double));
            $$ = *(double *) $1->pValue = $3;
        } else {
            $1->pValue= (int*) malloc(sizeof(int));
            $$ = *(int *) $1->pValue = $3;
        }
    }
;

ident   : IVAR | FVAR | UNDEF
        ;

%%


void yyerror(char *err) {
    printf("%s\n", err);
}

void printFloat(float token) {
        if (isFloat) {
                printf(" = %lf\n\n", token);
        }
        else {
                printf(" = %d\n\n", (int) token);
        }
        isFloat = 0;
}

int main(int argc, char **argv) {
        yyparse();
        return 0;
}
