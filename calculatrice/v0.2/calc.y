
%{
#include <stdio.h>
extern int yylex(void);
void yyerror(char *s);
%}

%token ADD SUB RC
%token NBR

%start list

%%
        list : /* VIDE */
        | list expr RC {printf("%i \n", $2);}
        | list RC
        ;

        expr : NBR ADD NBR      { $$ = $1 + $3; puts("Addition : ");}
        | NBR SUB NBR           { $$ = $1 - $3; puts("Soustraction : ");}
        ;
%%

void yyerror(char *s) {
        printf("%s\n", s);
}

int main () { 
    yyparse() ;
    return 0;
}