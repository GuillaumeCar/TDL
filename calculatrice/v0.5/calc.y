
%{
#include <stdio.h>
extern int yylex(void);
void yyerror(char *s);
int accus[26];
%}

%token ADD SUB AFF RC
%token NBR ACC

%start list
%union {
    int iVal;
    double dVal;
}

%%
list : /* VIDE */
    | list expr RC {printf("%i \n", $2);}
    | list assign RC {printf("%i \n", $2);}
    | list RC
    ;

assign : 
    ACC AFF NBR { $$ = accus[$1] = $3; puts("Assignation"); }
    ;

expr : 
    val ADD val { $$ = $1 + $3; puts("Addition : ");}
    | val SUB val { $$ = $1 - $3; puts("Soustraction : ");}
    | val { $$ = $1; puts("Valeur : ");}
    ;
val : 
    NBR { $$ = $1; }
    | ACC { $$ = accus[$1]; }
    ;
%%

void yyerror(char *s) {
    printf("%s\n", s);
}

int main () { 
    yyparse() ;
    return 0;
}