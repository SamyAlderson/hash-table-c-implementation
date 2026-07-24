CC=gcc
CFLAGS=-Wall -Wextra -std=c11

SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
BIN=hash-table-c-implementation

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(BIN)

test:
	@echo "No tests configured"

.PHONY: all clean test
