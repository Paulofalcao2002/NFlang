#!/bin/bash

bison -d -o src/parser.tab.c src/parser.y
flex -o src/lex.yy.c src/lexer.l
g++ -o nfl src/lex.yy.c src/parser.tab.c src/nodes.cpp src/prePro.cpp src/main.cpp
