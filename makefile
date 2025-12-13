
CC = gcc

SRC := $(wildcard src/*.c)
BIN := $(SRC:.c=.bin)

.PHONY: all clean

all: $(BIN)

%.bin: %.c
	$(CC) $< -o $@

clean:
	rm -f $(BIN)

