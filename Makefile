all: run

func.o: func.c param.h
	gcc -std=c99 -c func.c

main.o: main.c param.h
	gcc -std=c99 -c main.c

compile: main.o func.o param.h
	gcc -std=c99 -o main main.o func.o

run: compile
	./main

clean:
	rm -f main *.o

distclean: clean
	rm -f *.dat
