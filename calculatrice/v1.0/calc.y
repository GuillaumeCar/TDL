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
        int iVal;
        double dVal;
        pSymbol_t symb;
}

%token ADD SUB RC AFF MUL DIV EQ NEQ AND OR
%token <iVal> NBR
%token <dVal> FLO
%token <symb> UNDEF IVAR FVAR

%type <dVal> expr valeur assign
%type <symb> ident

%right AFF
%left ADD SUB
%left MUL DIV
%nonassoc UMINUS

%start list

%%
list    :   /* VIDE */
        | list expr RC      {   printFloat($2); }
        | list assign RC    {   printFloat($2); }
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

valeur  : NBR { $$ = $1; }
        | FLO { $$ = $1; isFloat = 1; }
        | IVAR { $$ = $1->U.iVal; } /* On montre la valeur de l'accumulateur */
        | FVAR { $$ = $1->U.dVal; isFloat = 1; } /* On montre la valeur de l'accumulateur */
        | UNDEF { yyerror("Variable non définie !"); yyerrok; }
        ;

assign  : ident AFF expr { 
                        if (isFloat) {
                                $1->type = FVAR; 
                                $$ = $1->U.dVal = $3;
                        } else {
                                $1->type = IVAR;
                                $$ = $1->U.iVal = $3;
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
