CC = gcc

SRC := $(wildcard src/*.c)
BIN := $(patsubst src/%.c,bin/%.bin,$(SRC))

.PHONY: all clean
all: bin $(BIN)

bin:
	mkdir -p bin

bin/%.bin: src/%.c
	$(CC) $< -o $@ -lreadline

clean:
	rm -f bin/*.bin bin/*.out
