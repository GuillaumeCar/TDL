
%%
0|([1-9][0-9]*)   printf("entier : %d\n", atoi(yytext));
"+"     puts("addition");
"-"     puts("soustraction");
\n      ;
.       ;
%%

int main() {
    yylex();
    return 0;
}