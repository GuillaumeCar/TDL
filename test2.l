%{
    #include <stdio.h>
    #define ENTIER 270
    #define RC 259
    #define IDENTIFIER 300
%}
%%
"0"|([1-9][0-9]*)   return ENTIER;
"quit"  return 0;
[a-zA-Z0-9_]*   return IDENTIFIER;
\n  return RC;
. ;
%%
int main () {
    int res;
    while((res=yylex()) != 0) {
        switch(res) {
            case ENTIER: printf("Ceci est un entier : %s\n",  yytext);break;
            case RC: puts("Ceci est un retour chariot");break;
            case IDENTIFIER: printf("Token secret : %s\n", yytext);break;
            default: puts("nul/20");
        }
    }
}
