CC=gcc
CFLAGS=-Wall -Wextra -pedantic
LDFLAGS=-lm

all: main

main: main.o
	gcc $(LDFLAGS) -o main main.o

main.o: main.c
	gcc $(CFLAGS) -c main.c

clean:
	rm -f main.o main

.PHONY: all clean