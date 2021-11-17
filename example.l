entier  [0-9]+
nl      \n
sortie  (quit|exit|ciao|bye)
%%
{entier}    ECHO;
{nl}        ECHO;
{sortie}    return 0;
.           ;
%%
int main () {
    yylex();
    return 0;
}