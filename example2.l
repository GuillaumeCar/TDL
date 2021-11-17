%%
int compt=0;
[ \t] ;
\n {compt=0};
[^ \t\n] {compt++; if (compt==2) ECHO;}
%%
int main (int argc, char **argv) {
    if (argc<2) {
        printf("usage : %s\
        filenameToBeAnalysed\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (yyin=fopen(argv[1],"r")) {
        yylex();
    } else {
        printf("Erreur d'ouverture de %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCES);
}