#!/bin/bash

bison -d parser.y
flex lexer.l
gcc -o nfl lex.yy.c parser.tab.c
