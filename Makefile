CC=gcc

CFLAGS=-g -O0 -std=c99 -pthread

all: grade gradet

test: roteador.c test.c
	$(CC) $(CFLAGS) -o test roteador.c test.c

testt: roteadort.c test.c
	$(CC) $(CFLAGS) -o testt roteadort.c test.c


grade: test
	./test

gradet: testt
	./testt

clean:
	rm -rf *.o test testt
