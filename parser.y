%{
#include <stdio.h>    
#include <stdlib.h>
#include <iostream>
#include <string>

#include "nodes.h"
using namespace std;

int yylex(); 

void yyerror(const char *s) {
    // Define the yyerror function
    fprintf(stderr, "Error: %s\n", s);
}

Node* makeNoOp() {
    return new Number(0, vector<unique_ptr<Node>>());
}

Node* makeSignal() {
    return new Signal(0, vector<unique_ptr<Node>>());
}

Node* makeString(string *str) {
    return new String(*str, vector<unique_ptr<Node>>());
}

Node* makeNumber(int value) {
    return new Number(value, vector<unique_ptr<Node>>());
}

Node* makeIdentifier(string *identifier) {
    return new Identifier(*identifier, vector<unique_ptr<Node>>());
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

Node* makePureVarDeclaration(string *type, string *identifier) {
    vector<unique_ptr<Node>> children;
    Node* identifierNode = makeIdentifier(identifier);
    children.emplace_back(unique_ptr<Node>(identifierNode));
    return new VarDeclaration(*type, move(children));
}

Node* makeVarDeclarationWithAssignment(string *type, string *identifier, Node *expression) {
    vector<unique_ptr<Node>> children;
    Node* identifierNode = makeIdentifier(identifier);
    children.emplace_back(unique_ptr<Node>(identifierNode));
    children.emplace_back(unique_ptr<Node>(expression));
    return new VarDeclaration(*type, move(children));
}

Node* makeAssignment(string *identifier, Node *expression) {
    vector<unique_ptr<Node>> children;
    Node* identifierNode = makeIdentifier(identifier);
    children.emplace_back(unique_ptr<Node>(identifierNode));
    children.emplace_back(unique_ptr<Node>(expression));
    return new Assignment(0, move(children));
}

Node* makeCall(Node *child) {
    vector<unique_ptr<Node>> children;
    children.emplace_back(unique_ptr<Node>(child));
    return new Call(0, move(children));
}

Node* makeWhenConditionalWithOneBlock(Node *condition, Node *block) {
    vector<unique_ptr<Node>> children;
    children.emplace_back(unique_ptr<Node>(condition));
    children.emplace_back(unique_ptr<Node>(block));
    return new WhenConditional(0, move(children));
}

Node* makeWhenConditionalWithTwoBlocks(Node *condition, Node *whenBlock, Node *otherwiseBlock) {
    vector<unique_ptr<Node>> children;
    children.emplace_back(unique_ptr<Node>(condition));
    children.emplace_back(unique_ptr<Node>(whenBlock));
    children.emplace_back(unique_ptr<Node>(otherwiseBlock));
    return new WhenConditional(0, move(children));
}

Node* makePlayUntil(Node *condition, Node *block) {
    vector<unique_ptr<Node>> children;
    children.emplace_back(unique_ptr<Node>(condition));
    children.emplace_back(unique_ptr<Node>(block));
    return new PlayUntil(0, move(children));
}

Node* makeDrive(string *type, string *identifier, Node *leftValue, Node *rightValue, Node *block) {
    vector<unique_ptr<Node>> children;

    Node* variableDeclarationNode = makeVarDeclarationWithAssignment(type, identifier, leftValue);
    children.emplace_back(unique_ptr<Node>(variableDeclarationNode));
    children.emplace_back(unique_ptr<Node>(rightValue));
    children.emplace_back(unique_ptr<Node>(block));
    return new Drive(0, move(children));
}

Node* makeFunctionDeclarationWithoutArgs(string *type, string *identifier, Node *block) {
    vector<unique_ptr<Node>> children;

    Node* functionVarDec = makePureVarDeclaration(type, identifier);
    children.emplace_back(unique_ptr<Node>(functionVarDec));
    children.emplace_back(unique_ptr<Node>(block));
    return new FunctionDeclaration(0, move(children));
}

Node* makeFunctionDeclarationWithArgs(string *type, string *identifier, Node *arguments, Node *block) {
    vector<unique_ptr<Node>> children;

    Node* functionVarDec = makePureVarDeclaration(type, identifier);
    children.emplace_back(unique_ptr<Node>(functionVarDec));

    for (auto& argument : arguments->children) {
        children.emplace_back(std::move(argument));
    }

    children.emplace_back(unique_ptr<Node>(block));
    return new FunctionDeclaration(0, move(children));
}

Node* makeFunctionCallWithoutArgs(string *identifier) {
    return new FunctionCall(*identifier, vector<unique_ptr<Node>>());
}

Node* makeFunctionCallWithArgs(string *identifier, Node *arguments) {
    vector<unique_ptr<Node>> children;

    for (auto& argument : arguments->children) {
        children.emplace_back(std::move(argument));
    }

    return new FunctionCall(*identifier, move(children));
}

Node* makeResult(Node *expression) {
    vector<unique_ptr<Node>> children;
    children.emplace_back(unique_ptr<Node>(expression));

    return new Result(0, move(children));
}

Node* makeBlock() {
    return new Block(0, vector<unique_ptr<Node>>());
}

%}

%union {
    string *stringValue;
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
%token WHEN THEN OTHERWISE DRIVE ON PLAY_UNTIL BREAK_LINE ACTION L_BRACKET R_BRACKET RESULT

// Dynamic values tokens
%token IDENTIFIER NUMBER STRING POSITION DOWN TYPE

%type <nodePtr> program block statements statement result func_declaration declaration_arguments call_arguments drive_loop play_until when_conditional variable_declaration assignment call boolean_expression boolean_term relative_expression expression term factor
%type <number> NUMBER
%type <stringValue> IDENTIFIER STRING TYPE DOWN SIGNAL

%%

program: statements { 
    SymbolTable* symbolTable = new SymbolTable();
    $1->evaluate(*symbolTable); 
};

statements: statement { $$ = makeBlock(); $$->children.emplace_back(unique_ptr<Node>($1)); }
    | statements statement  { $1->children.emplace_back(unique_ptr<Node>($2)); }
    ;

statement: BREAK_LINE { $$ = makeNoOp(); }
    | result BREAK_LINE
    | func_declaration BREAK_LINE
    | drive_loop BREAK_LINE
    | play_until BREAK_LINE
    | when_conditional BREAK_LINE
    | variable_declaration BREAK_LINE
    | assignment BREAK_LINE
    | call BREAK_LINE
    ;

block: L_BRACKET R_BRACKET { $$ = makeNoOp(); }
    | L_BRACKET statements R_BRACKET { $$ = $2; }
    ;

result: RESULT boolean_expression { $$ = makeResult($2); };

func_declaration: ACTION TYPE IDENTIFIER L_PARENTHESIS R_PARENTHESIS block 
    { $$ = makeFunctionDeclarationWithoutArgs($2, $3, $6); }
    | ACTION TYPE IDENTIFIER L_PARENTHESIS declaration_arguments R_PARENTHESIS block
    { $$ = makeFunctionDeclarationWithArgs($2, $3, $5, $7); }
    ;

declaration_arguments: TYPE IDENTIFIER 
    { $$ = makeBlock(); $$->children.emplace_back(unique_ptr<Node>(makePureVarDeclaration($1, $2))); }
    | declaration_arguments COMMA TYPE IDENTIFIER
    { $1->children.emplace_back(makePureVarDeclaration($3, $4)); }
    ;

drive_loop: DRIVE TYPE IDENTIFIER ON L_PARENTHESIS boolean_expression COMMA boolean_expression R_PARENTHESIS block
    { $$ =  makeDrive($2, $3, $6, $8, $10); }
    ;

play_until: PLAY_UNTIL boolean_expression block { $$ = makePlayUntil($2, $3); }

when_conditional: WHEN boolean_expression THEN block { $$ = makeWhenConditionalWithOneBlock($2, $4); }
    | WHEN boolean_expression THEN block OTHERWISE block { $$ = makeWhenConditionalWithTwoBlocks($2, $4, $6); }
    ;

variable_declaration: TYPE IDENTIFIER { $$ = makePureVarDeclaration($1, $2); }
    | TYPE IDENTIFIER IS boolean_expression { $$ = makeVarDeclarationWithAssignment($1, $2, $4); }
    ;

assignment: IDENTIFIER IS boolean_expression { $$ = makeAssignment($1, $3); }
    | IDENTIFIER L_PARENTHESIS R_PARENTHESIS { $$ = makeFunctionCallWithoutArgs($1); }
    | IDENTIFIER L_PARENTHESIS call_arguments R_PARENTHESIS { $$ = makeFunctionCallWithArgs($1, $3); }
    ;

call_arguments: boolean_expression { $$ = makeBlock(); $$->children.emplace_back(unique_ptr<Node>($1)); }
    | call_arguments COMMA boolean_expression { $1->children.emplace_back($3); }
    ;

call: CALL L_PARENTHESIS boolean_expression R_PARENTHESIS { $$ = makeCall($3); };

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
    | IDENTIFIER { $$ = makeIdentifier($1); }
    | STRING { $$ = makeString($1); }
    | DOWN { $$ = makeString($1); }
    | SIGNAL L_PARENTHESIS R_PARENTHESIS { $$ = makeSignal(); }
    | IDENTIFIER L_PARENTHESIS R_PARENTHESIS { $$ = makeFunctionCallWithoutArgs($1); }
    | IDENTIFIER L_PARENTHESIS call_arguments R_PARENTHESIS { $$ = makeFunctionCallWithArgs($1, $3); }
    ;

%%
