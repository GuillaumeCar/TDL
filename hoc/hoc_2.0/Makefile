YFLAGS=-d
SRCS=hoc.l hoc.y hoc.h symbol.h symbol.c defSymbols.c color.h color.c io.h io.c msgFmt.c codeHoc.h codeHoc.c code.h code.c
OBJS=hoc.o hoc.l.o symbol.o color.o io.o codeHoc.o code.o
#DBG=-D DBG_LEX -D DBG_YACC -D DBG_CODE -D DBG_EXE
DBG=
CC=gcc

hoc: $(OBJS)
	gcc $(OBJS) -o hoc -ll -lm
	make clean
	
hoc.o: hoc.h symbol.h io.h hoc.y
	bison $(YFLAGS) hoc.y
	mv hoc.tab.c hoc.c
	gcc -c $(DBG) hoc.c

hoc.l.o: hoc.h hoc.tab.h symbol.h io.h hoc.l
	flex -I hoc.l
	gcc -c $(DBG) lex.yy.c -o hoc.l.o
	rm lex.yy.c

symbol.o: hoc.h hoc.tab.h symbol.h symbol.c defSymbols.c
	gcc -c  $(DBG) symbol.c

color.o: hoc.h color.h color.c
	gcc -c  $(DBG) color.c

io.o: hoc.h symbol.h color.h io.h io.c msgFmt.c
	gcc -c  $(DBG) io.c

codeHoc.o: hoc.h io.h io.c codeHoc.h codeHoc.c
	gcc -c  $(DBG) codeHoc.c

code.o: hoc.h io.h io.c codeHoc.h codeHoc.c code.h code.c
	gcc -c  $(DBG) code.c

clean:
	rm -f $(OBJS) hoc.tab.h hoc.c lex.yy.c *~

edit:
	gedit $(SRC) &
