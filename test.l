%{
    #include <stdio.h>
%}
%%
[a-zA-Zéèàçùêâîôû]    printf("--> lettre %s\n", yytext);
[a-zA-Zéèàçùêâîôû]*    printf("--> mot %s\n", yytext);
[a-zA-Zéèàçùêâîôû ]*    printf("--> phrase %s\n", yytext);
[0-9]?  printf("--> chiffre %s\n", yytext);
0|[1-9][0-9]*   printf("--> nombre %s\n", yytext);
. ;
%%
int main () {
    yylex();
}
