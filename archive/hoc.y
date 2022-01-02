%{
	#include "hoc.h"
	#include "math.h"
	#include <signal.h>
	#include <stdio.h>
	#include <setjmp.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <unistd.h>

	void Prompt(void){
		printf("calc> ");
	}

	void yyerror(char *);
%}

%union {
      double Value;
      Symbol *Symb;
}

	

%token <Value> NUMBER
%token <Symb>  VAR PREDEF UNDEF
%token PRINT
%token ADD SUB MUL DIV POW RC;

%type  <Value> expr asgn


%left ADD SUB               
%left MUL DIV

%left  UNARYMINUS 

%right POW

%%

list:    		/* Vide */
	| list RC
	| list asgn  RC  { Prompt(); }
	| list expr  RC  { printf("= %.8g\n", $2); Prompt(); }
	| list error RC  { yyerrok; Prompt(); }
	| list help  RC	 { Prompt(); }
	;

asgn:	VAR '=' expr { $$ = $1->U.Value = $3; $1->Type = VAR;}
 	;

help:
	PRINT {PrintSymbolList();}

expr:	NUMBER           { $$ = $1; }
	| VAR            { $$ = $1->U.Value; 
	    if ($1->Type == UNDEF) ExecError("Undefined variable -", $1->Name);}
	| asgn
	| PREDEF '(' expr ')' {
	     if ($1->Type != PREDEF) ExecError("Undefined function -", $1->Name);
	     $$ = (*($1->U.Func)) ($3); }
	| '(' expr ')'   { $$ = $2; }
	| expr ADD expr  { $$ = $1 + $3; }
	| expr SUB expr  { $$ = $1 - $3; }
	| expr MUL expr  { $$ = $1 * $3; }
	| expr DIV expr  { 
	     if ($3 == 0.0) raise(SIGFPE); /* ExecError("Divide by zero", "");*/
	     $$ = $1 / $3; }
	| expr POW expr  { $$ = pow($1, $3); }
	| SUB expr %prec UNARYMINUS { $$ = -$2; }
	
	;

%%

	char* ProgName;
	int LineNo = 0;
	jmp_buf Begin;


	int main (int ArgC, char *ArgV[])
	{    void FpeCatch();

	     ProgName = ArgV[0];
	     fprintf(stdout,"Welcome to the basic calculator - Version 1.0\n");
	     Init();
	     if (signal(SIGFPE, SIG_IGN) != SIG_IGN)
	        signal(SIGFPE, FpeCatch); /* Trap les erreurs arithmetiques */
	     setjmp(Begin);        /* Tag du context avec le label "Begin" */
	     Prompt();
	     yyparse();            /* yyparse() a besoin de yylex() */
	     fprintf(stdout, "logout\nI hope to see you nice !!\n");
	}

	void yyerror(char *Mess){    
		fprintf(stderr, "%s:", ProgName);
	     if (Mess) fprintf(stderr, " %s", Mess);
	     //if (Type) fprintf(stderr, " %s", Type);
	     fprintf(stderr, " (at line %d)\n", LineNo);
	}

	void ExecError(char *Mess, char *Type){    
		yyerror(Mess);
	    longjmp(Begin, 0);
	}

	void FpeCatch(){   
		signal(SIGFPE, FpeCatch); /* Trap les erreurs arithmetiques */
	    ExecError("Arithmetic error", NULL);
	}