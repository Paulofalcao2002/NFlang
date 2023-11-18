#!/bin/bash

bison -d parser.y
flex lexer.l
g++ -o nfl lex.yy.c parser.tab.c nodes.cpp -lfl -std=c++11
