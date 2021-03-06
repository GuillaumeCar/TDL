
%{
#include <stdio.h>
extern int yylex(void);
void yyerror(char *s);
int accus[26];
double accusDouble[26];
int isFloat = 0;
%}

%union {
    int iVal;
    double dVal;
}

%token ADD SUB AFF RC
%token <iVal> NBR ACCI ACCD
%token <dVal> FLT

%type <dVal> expr assign val

%start list

%%
list : /* VIDE */
    | list expr RC {printf("--->%f \n", $2);}
    | list assign RC {printf("--->%f \n", $2);}
    | list error RC {yyerrok;}
    | list RC
    ;

assign : 
    ACCI AFF expr { $$ = accus[$1] = $3; puts("Assignation"); }
    | ACCD AFF expr { $$ = accusDouble[$1] = $3; puts("Assignation double"); }
    ;

expr : 
    expr ADD expr { $$ = $1 + $3; puts("Addition : ");}
    | expr SUB expr { $$ = $1 - $3; puts("Soustraction : ");}
    | SUB val { $$ = -$2; }
    | val { $$ = $1; }
    ;
val : 
    NBR { $$ = $1; isFloat = 0; }
    | FLT { $$ = $1; isFloat = 1; }
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