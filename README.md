# NFLang

Programming language created to sketch Football plays and strategies.

## Syntax Diagram

![SyntaxDiagram](SyntaxDiagram.svg)

## EBNF

    PROGRAM = { STATEMENT | DECLARATION };

    DECLARATION = "action", TYPE, IDENTIFIER, "(", (λ | DECLARATION_ARGUMENTS) ")", DECLARATION_BLOCK, "\n";
    DECLARATION_ARGUMENTS = IDENTIFIER, TYPE, {",", IDENTIFIER, TYPE};
    DECLARATION_BLOCK = "{", { STATEMENT | ("result", GENERAL_EXPRESSION) }, "}";


    STATEMENT = ( λ | ASSIGNMENT | CALL | WHEN_CONDITIONAL | DRIVE_LOOP | VARDEC | PLAYUNTIL_LOOP), "\n" ;

    ASSIGNMENT = IDENTIFIER, ("is", GENERAL_EXPRESSION) | ACTION_CALL_ARGUMENTS ;
    ACTION_CALL_ARGUMENTS = "(", λ | (GENERAL_EXPRESSION, {",", GENERAL_EXPRESSION}) ")";

    CALL = "call", "(", BOOLEAN_EXPRESSION, ")" ;
    WHEN_CONDITIONAL = "when", BOOLEAN_EXPRESSION, "then", BLOCK, (λ | ("otherwise", BLOCK));
    DRIVE_LOOP = "drive", TYPE, IDENTIFIER, "on", "(", EXPRESSION, ",", EXPRESSION, ")", BLOCK;
    VARDEC = TYPE, IDENTIFIER, (λ | ("is", GENERAL_EXPRESSION));
    PLAYUNTIL_LOOP = "playuntil", BOOLEAN_EXPRESSION, BLOCK;
    BLOCK = "{", { STATEMENT }, "}";

    GENERAL_EXPRESSION = PLAY_EXPRESSION | BOOLEAN_EXPRESSION;

    PLAY_EXPRESSION = "{", λ | (PLAY_DEFINITION, {",", PLAY_DEFINITION}), "}";
    PLAY_DEFINITION = POSITION, ":", STRING;

    BOOLEAN_EXPRESSION = BOOLEAN_TERM, {"or", BOOLEAN_TERM}; 
    BOOLEAN_TERM = RELATIVE_EXPRESSION, {"and", RELATIVE_EXPRESSION}; 
    RELATIVE_EXPRESSION = EXPRESSION, {("equals" | ">" | "<"), EXPRESSION}; 

    EXPRESSION = TERM, { ("+" | "-"), TERM } ;
    TERM = FACTOR, { ("*" | "/"), FACTOR } ;
    FACTOR = (("+" | "-" | "not", ">>"), FACTOR) | NUMBER | STRING | DOWN | ("(", BOOLEAN_EXPRESSION, ")") | IDENTIFIER, (λ | ACTION_CALL_ARGUMENTS)  | ("signal", "(", ")") ;

    IDENTIFIER = LETTER, { LETTER | DIGIT | "_" } ;
    TYPE = "athlete" | "play" | "number" | "down" | "empty";
    DOWN = "FirstDown" | "SecondDown" | "ThirdDown" | "FourthDown";
    POSITION = "QB" | "WR" | "TE" | "RB" | "FB" | "OL" | "DL" | "LB" | "CB" | "S" | "K" | "P";


    STRING = """, { LETTER }, """;
    NUMBER = DIGIT, { DIGIT } ;
    LETTER = ( a | ... | z | A | ... | Z ) ;
    DIGIT = ( 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 ) ;