#!/bin/bash

echo "Compilando com flags para debug"
gcc -g -O0 -Wall -Wextra -lreadline ./src/main.c -o ./bin/a.out
gdb ./bin/a.out -q
