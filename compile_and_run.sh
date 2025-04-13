#!/bin/bash
gcc -Wall -Wextra syntax_analyser/syntax_analyser.c syntax_analyser/stack.c syntax_analyser/tree.c lexer/lexer.c -o syntax_analyser/parser
./syntax_analyser/parser "programa_foda" 