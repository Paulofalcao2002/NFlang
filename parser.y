%{
#include <stdio.h>    
#include <stdlib.h>
#include <iostream>
#include "nodes.h"
using namespace std;

int yylex(); 

void yyerror(const char *s) {
    // Define the yyerror function
    fprintf(stderr, "Error: %s\n", s);
}

Node* makeNumber(int value) {
    return new Number(value, vector<unique_ptr<Node>>());
}

Node* makeUnOp(int operation, Node *child) {
    vector<unique_ptr<Node>> children;
    children.emplace_back(unique_ptr<Node>(child));
    return new UnOp(operation, move(children));
}

Node* makeBinOp(int operation, Node *left, Node *right) {
    vector<unique_ptr<Node>> children;
    children.emplace_back(unique_ptr<Node>(left));
    children.emplace_back(unique_ptr<Node>(right));
    return new BinOp(operation, move(children));
}


%}

%union {
    char *string;
    int number;
    Node *nodePtr;
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

%type <nodePtr> boolean_expression boolean_term relative_expression expression term factor
%type <number> NUMBER

%%

program: boolean_expression { printf("result: %d\n", $1->evaluate()); };

boolean_expression: boolean_expression OR boolean_term { $$= makeBinOp((int) BinOperation::OR, $1, $3); }
    | boolean_term { $$= $1; }
    ;

boolean_term: boolean_term AND relative_expression { $$= makeBinOp((int) BinOperation::AND, $1, $3); }
    | relative_expression { $$= $1; }
    ;

relative_expression: relative_expression EQUALS expression { $$ = makeBinOp((int) BinOperation::EQUALS, $1, $3); }
    | relative_expression GREATER_THAN expression { $$ = makeBinOp((int) BinOperation::GREATER_THAN, $1, $3); }
    | relative_expression LESSER_THAN expression { $$ = makeBinOp((int) BinOperation::LESSER_THAN, $1, $3);}
    | expression { $$= $1; }
    ;

expression: expression PLUS term { $$ = makeBinOp((int) BinOperation::PLUS, $1, $3); }
          | expression MINUS term { $$ = makeBinOp((int) BinOperation::MINUS, $1, $3); }
          | term { $$ = $1; }
          ;

term: term TIMES factor { $$ = makeBinOp((int) BinOperation::TIMES, $1, $3); }
    | term DIVIDE factor { $$ = makeBinOp((int) BinOperation::DIVIDE, $1, $3); }
    | factor { $$ = $1; }
    ;

factor: NUMBER { $$= makeNumber($1); }
    | L_PARENTHESIS boolean_expression R_PARENTHESIS {$$ = $2; }
    | PLUS factor { $$ = makeUnOp((int) UnOperation::PLUS, $2); }
    | MINUS factor { $$ = makeUnOp((int) UnOperation::MINUS, $2);  }
    | INCREMENT factor {$$ = makeUnOp((int) UnOperation::INCREMENT, $2); }
    | NOT factor { $$ = makeUnOp((int) UnOperation::NOT, $2);  }
    ;

%%
