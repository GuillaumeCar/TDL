%{
	int lineCpt = 0;
	int wordCpt = 0;
	int carCpt = 0;
%}

%%
[^\t\n ]+	{ wordCpt++;carCpt+=yyleng; };
\n			{ lineCpt++;carCpt++; };
[ \t]		{ carCpt+=yyleng; };

%%

int main(int argc, char** argv){
	if (argc != 2) {
		puts("./exe <file>");
		exit(1);
	}

	if ((yyin = fopen(argv[1],"r")) == NULL){
		printf("File not found : %s\n", argv[1]);
		exit(2);
	}

	yylex();
	
	printf("%d %d %d %s\n", lineCpt, wordCpt, carCpt, argv[1]);
    
	return 0;
}