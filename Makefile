CC=gcc
CFLAGS=-Wall -Wextra -pedantic
LDFLAGS=-lm

all: main

main: main.o
	$(CC) $(LDFLAGS) main.o -o main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f main.o main