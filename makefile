CC = gcc
SRC := $(wildcard *.c)
BIN := $(patsubst %.c, %.bin, $(SRC))
all : $(BIN)

%.bin: %.c

		$(CC) $< -o $@
