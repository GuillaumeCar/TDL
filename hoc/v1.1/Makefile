all: exe

exe: lex symbol
	gcc lex.yy.c hoc.tab.c symbol.c -o exe -ll -lm

lex: hoc.l bison symbol
	lex hoc.l

symbol: symbol.c
	gcc -c symbol.c

bison: hoc.y
	bison -d hoc.y

clean:
	rm -rf lex.yy.c hoc.tab.c hoc.tab.h exe symbol.o
