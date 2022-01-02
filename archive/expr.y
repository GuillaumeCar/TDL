%{
	#include "expr.h"
%}
%union {
	double value;
	Psymbol symbol;
	InsMac *refCode; // instruction machine
}
%token<symbol> NUMBER VAR UNDEF PREDEF DEF IF ELSE
%type<refCode> expr stmt asgn cond if fi block
%token PRINT

%right '='
%left	LOG_OR
%left	LOG_AND
%left SUP INF EQ
%left '+' '-'
%left '*' '/'
%left UNARYMINUS
%right '#'

%%

list:
	| list '\n'	{ Code(STOP); return 1;}
	//| list func '\n' { printf("func\n"); prompt();}
	| list asgn '\n'	{ printf("asgn\n"); Code(STOP); return 1; }
	| list stmt '\n'	{ printf("stmt\n"); Code(STOP); return 1; }
	| list expr '\n'	{ printf("expr\n"); Code2(PrintExpr, STOP); return 1; }
	| list error '\n'	{ printf("error\n"); yyerrok; prompt();}
	| list help '\n' { printf("help\n"); prompt();}
	;
asgn:	VAR '=' expr	{ $$=$3; Code3(VarPush, (InsMac) $1, Assign); }
	| UNDEF '=' expr	{ $$=$3; Code3(VarPush, (InsMac) $1, Assign); }
	;
stmt:	expr	{ printf("stmt is expr\n"); Code(Pop); }
	| PRINT expr	{ printf("stmt 2\n"); Code(PrintExpr); $$=$2;}
	| if cond stmt fi	{ printf("stmt 3\n"); ($1)[1] = (InsMac) $3; ($1)[3] = (InsMac) $4; }
	| if cond stmt fi ELSE stmt fi	{ printf("stmt 4\n"); ($1)[1] = (InsMac)$3;	 ($1)[2] = (InsMac)$6; ($1)[3] = (InsMac)$7; }
	| '{' block '}'	{ printf("stmt 5\n"); $$=$2; }
	;
cond:	'{' expr '}'	{ printf("cond\n"); Code(STOP); $$=$2; }
	;
if:	IF	{ printf("if\n"); $$=Code(ifCode); printf("if2\n"); Code3(STOP, STOP, STOP); printf("if3\n"); }
	;
fi:	{ printf("fi\n"); Code(STOP); $$=ProgPtr; }
	;
/*func:	UNDEF '(' ')' '{' block '}'	{ $1->type = DEF; printf("Nouvelle fonction\n"); }
	| DEF '(' ')' '{' block '}'	{ printf("Redef\n"); }
	;*/
block:	{ $$=ProgPtr; }
	| stmt ';'
	| block stmt
	;
expr:	NUMBER	{ Code2(NbrPush, (InsMac) $1); }
	| VAR	{ Code3(VarPush, (InsMac) $1, Eval); }
	| asgn
	| PREDEF '(' expr ')'	{ $$=$3; Code2(Predef, (InsMac) $1->U.func); }
	| '(' expr ')'	{ $$ = $2; }
	| expr '+' expr { Code(Add); }
	| expr '-' expr { Code(Sub); }
	| expr '*' expr { Code(Mul); }
	| expr '/' expr { Code(Div); }
	| expr '#' expr	{ Code(Power); }
	| '-' expr %prec UNARYMINUS { Code(Negate); }
	| expr SUP expr { Code(Sup); }
	| expr INF expr { Code(Inf); }
	| expr EQ expr { Code(Equals); }
	| expr LOG_AND expr { Code(And); }
	| expr LOG_OR expr { Code(Or); }
	| DEF '(' ')' { printf("appel a une fonction\n"); }
	;
help:	PRINT { printSymbolList(); }
	;
%%

char * progName;
int lineNo = 0;

void warning(const char * mess, const char * type) {
	fprintf(stderr, "%s :--", progName);
	if (mess) { fprintf(stderr, "%s--", mess);}
	if (type) { fprintf(stderr, "%s--", type);}
	fprintf(stderr, " at line %d--\n", lineNo);
}

yyerror(const char * mess) {
	warning(mess, NULL);
}

void prompt(void) {
	fprintf(stdout, "> ");
}

void initCode(void) {
	prompt();
	ProgPtr = Prog;
	PC = Prog;
	StackPtr = Stack;
}

int main(int argc, char* argv[]) {
	progName = argv[0];
	fprintf(stdout, "\nCalculatrice\n\n");
	init();
	for(initCode(); yyparse(); Execute(Prog), initCode());
	fprintf(stdout, "Bye\n");
	exit(EXIT_SUCCESS);
}
