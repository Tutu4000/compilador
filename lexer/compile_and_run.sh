#!/bin/bash
gcc -o compiler main.c lexer.c -Wall -Wextra
./compiler test.txt
