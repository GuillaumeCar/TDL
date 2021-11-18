
%{
#include <stdio.h>
extern int yylex(void);
void yyerror(char *s);
int accus[26];
double accusDouble[26];
%}

%union {
    int iVal;
    double dVal;
}

%token ADD SUB AFF RC MUL
%token <iVal> NBR ACCI ACCD
%token <dVal> FLT

%type <dVal> expr assign val facteur terme

%start list

%%
list : /* VIDE */
    | list expr RC {printf("--->%f \n", $2);}
    | list assign RC {printf("--->%f \n", $2);}
    | list error RC {yyerrok;}
    | list RC
    ;

assign : 
    ACCI AFF NBR { $$ = accus[$1] = $3; puts("Assignation"); }
    | ACCD AFF val { $$ = accusDouble[$1] = $3; puts("Assignation double"); }
    ;

expr : 
    expr add terme { $$ = $1 + $3; puts("Addition : ");}
    | val { $$ = $1; puts("Valeur : ");}
    ;

terme : 
    terme MUL facteur { $$ = $1 * $3; puts("Multiplication : "); }
    | facteur { $$ = $1; }
    ;

facteur : 
    val { $$ = $1; puts("Valeur : ");}
    | assign
    ;

add : ADD | SUB
    ;

val : 
    NBR { $$ = $1; }
    | FLT { $$ = $1; }
    | ACCI { $$ = accus[$1]; }
    | ACCD { $$ = accusDouble[$1]; }
    ;
%%

void yyerror(char *s) {
    printf("%s\n", s);
}

int main () { 
    yyparse() ;
    return 0;
}