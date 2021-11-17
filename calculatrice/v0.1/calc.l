%%
[0-9]   printf("valeur : %d\n", atoi(yytext));
"+"     puts("addition");
"-"     puts("soustraction");
.       printf("Ignoré : [%s]\n", yytext);
%%

int main() {
    yylex();
    return 0;
}