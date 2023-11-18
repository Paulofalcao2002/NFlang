%{
#include <stdio.h>    
#include <stdlib.h>
int yylex(); 

%}

%union {
    char *string;
    int number;
};

// Arithmetic tokens
%token PLUS MINUS INCREMENT L_PARENTHESIS R_PARENTHESIS TIMES DIVIDE 

// Boolean/relative tokens
%token NOT EQUALS GREATER_THAN LESSER_THAN AND OR

// Variable definition tokens
%token IS COMMA COLON  

// IO tokens
%token SIGNAL CALL

// Code block tokens (If, else, for, while)
%token WHEN THEN OTHERWISE DRIVE ON PLAY_UNTIL BREAK_LINE ACTION L_BRACKET R_BRACKET  

// Dynamic values tokens
%token IDENTIFIER NUMBER STRING POSITION DOWN TYPE

%type <number> expression term factor NUMBER

%%

program: expression { printf("result: %d\n", $1); };

expression: expression PLUS term { $$ = $1 + $3; }
          | expression MINUS term { $$ = $1 - $3; }
          | term { $$ = $1; }
          ;

term: term TIMES factor { $$ = $1 * $3; }
    | term DIVIDE factor { $$ = $1 / $3; }
    | factor { $$ = $1; }
    ;

factor: NUMBER { $$ = $1; }
    | L_PARENTHESIS expression R_PARENTHESIS {$$ = $2; }
    | PLUS factor { $$ = +$2; }
    | MINUS factor { $$ = -$2; }
    | INCREMENT factor { $$ = $2 + 1; }
    ;

// program: type | down | position | string | number | identifier | plus | minus | not | increment | l_parenthesis | r_parenthesis | times | divide | equals | greater_than | lesser_than | and | or | comma | colon | l_bracket | r_bracket  | is | when | then | otherwise | drive | on | signal | play_until | call | break_line | action; 

// type: TYPE {
//     printf("This is type: %s\n", yylval.string);
//     exit(0);
// };

// down: DOWN {
//     printf("This is down: %s\n", yylval.string);
//     exit(0);
// };

// position: POSITION {
//     printf("This is position: %s\n", yylval.string);
//     exit(0);
// };

// string: STRING {
//     printf("This is string: %s\n", yylval.string);
//     exit(0);
// };

// number: NUMBER {
//     printf("This is number: %d\n", yylval.number);
//     exit(0);
// };

// identifier: IDENTIFIER {
//     printf("This is identifier: %s\n", yylval.string);
//     exit(0);
// };

// plus: PLUS {
//     printf("This is plus\n");
//     exit(0);
// };

// minus: MINUS {
//     printf("This is minus\n");
//     exit(0);
// };

// not: NOT {
//     printf("This is not\n");
//     exit(0);
// };

// increment: INCREMENT {
//     printf("This is increment\n");
//     exit(0);
// };

// l_parenthesis: L_PARENTHESIS {
//     printf("This is left parenthesis\n");
//     exit(0);
// };

// r_parenthesis: R_PARENTHESIS {
//     printf("This is right parenthesis\n");
//     exit(0);
// };

// times: TIMES {
//     printf("This is times\n");
//     exit(0);
// };

// divide: DIVIDE {
//     printf("This is divide\n");
//     exit(0);
// };

// equals: EQUALS {
//     printf("This is equals\n");
//     exit(0);
// };

// greater_than: GREATER_THAN {
//     printf("This is greater than\n");
//     exit(0);
// };

// lesser_than: LESSER_THAN {
//     printf("This is lesser than\n");
//     exit(0);
// };

// and: AND {
//     printf("This is AND\n");
//     exit(0);
// };

// or: OR {
//     printf("This is OR\n");
//     exit(0);
// };

// comma: COMMA {
//     printf("This is comma\n");
//     exit(0);
// };

// colon: COLON {
//     printf("This is colon\n");
//     exit(0);
// };

// l_bracket: L_BRACKET {
//     printf("This is left bracket\n");
//     exit(0);
// };

// r_bracket: R_BRACKET {
//     printf("This is right bracket\n");
//     exit(0);
// };

// is: IS {
//     printf("This is IS\n");
//     exit(0);
// };

// when: WHEN {
//     printf("This is WHEN\n");
//     exit(0);
// };

// then: THEN {
//     printf("This is THEN\n");
//     exit(0);
// };

// otherwise: OTHERWISE {
//     printf("This is OTHERWISE\n");
//     exit(0);
// };

// drive: DRIVE {
//     printf("This is DRIVE\n");
//     exit(0);
// };

// on: ON {
//     printf("This is ON\n");
//     exit(0);
// };

// signal: SIGNAL {
//     printf("This is SIGNAL\n");
//     exit(0);
// };

// play_until: PLAY_UNTIL {
//     printf("This is PLAY_UNTIL\n");
//     exit(0);
// };

// call: CALL {
//     printf("This is CALL\n");
//     exit(0);
// };

// break_line: BREAK_LINE {
//     printf("This is BREAK_LINE\n");
//     exit(0);
// };

// action: ACTION {
//     printf("This is ACTION\n");
//     exit(0);
// };

%%
