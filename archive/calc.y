%{
#include <stdlib.h>
#include <stdio.h>

void yyerror(const char *mess){
	printf("Erreur de syntax : %s\n", mess);
}
void prompt(void){printf("calc> ");}
int reg[26] = {0};
%}

%token NUM REG
%token RC ADD SUB MUL DIV

%right AFF
%left ADD SUB
%left MUL DIV
%nonassoc UNARYMINUS
%start list
%%


list : /*VIDE*/
		| list RC
		| list expr RC {printf("= %d\n", $2);prompt();}
		| list asgn RC {printf("= %d\n", $2);prompt();}
		| list error RC { yyerrok; prompt();}
	;
	
asgn :  REG AFF expr { $$=$3; reg[$1]=$3;}
	;

expr : NUM {$$ = $1 ; printf("NUM ");}
		| expr ADD expr {$$=$1+$3 ; printf("ADD ");}
		| expr SUB expr {$$=$1-$3 ; printf("SUB ");}
		| expr MUL expr {$$=$1*$3 ; printf("MUL ");}
		| expr DIV expr 
			{	if($3==0) {yyerror("Division par zéro");  YYERROR;}
				$$=$1/$3;}
		| REG { $$=reg[$1]; printf("Rreg "); }
		| SUB %prec UNARYMINUS expr {$$=-$2;}
		| '(' expr ')' { $$=$2; }
	;
%%

int main()
{
	printf("Bienvenue sur ma première calculatrice linguistaique\n");
	prompt();
	yyparse();
	printf("A bientôt \n");
	return 0;
}