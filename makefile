CC      = gcc
CFLAGS  = -Wall -Wextra -g -Iinclude
LDFLAGS = -lreadline

SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c,obj/%.o,$(SRC))

BIN := bin/app

.PHONY: all clean

all: $(BIN)

# Linkagem final
$(BIN): $(OBJ) | bin
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Compilação de cada .c -> .o
obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

# Diretórios
bin:
	mkdir -p bin

obj:
	mkdir -p obj

clean:
	rm -rf obj bin
