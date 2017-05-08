CC=gcc

CFLAGS=-g -O0 -std=c11 -lpthread 

all: grade gradet

test: roteador.c test.c
	$(CC) -o test roteador.c test.c

testt: roteadort.c test.c
	$(CC) -o test roteadort.c test.c


grade: test
	./test

gradet: testt
	./testt

clean:
	rm -rf *.o test testt
