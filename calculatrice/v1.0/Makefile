all: exe

exe: lex symboles
	gcc calc.tab.c lex.yy.c symboles.o -o exe -ll; rm calc.tab.c lex.yy.c

bison: calc.y
	bison -d calc.y

lex: bison calc.l
	lex calc.l
	
symboles: symboles.h symboles.c
	gcc -c symboles.c

clean:
	rm calc.tab.c exe lex.yy.c calc.tab.h
