# NFLang

Programming language created to sketch Football plays and strategies.

## Syntax Diagram

![SyntaxDiagram](SyntaxDiagram.svg)

## EBNF

    PROGRAM = { STATEMENT };

    STATEMENT = ( λ | ASSIGNMENT | CALL | WHEN_CONDITIONAL | DRIVE_LOOP | VARDEC | PLAYUNTIL_LOOP), "\n" ;
    ASSIGNMENT = IDENTIFIER, "is", GENERAL_EXPRESSION ;
    CALL = "call", "(", BOOLEAN_EXPRESSION, ")" ;
    WHEN_CONDITIONAL = "when", BOOLEAN_EXPRESSION, "then", BLOCK, (λ | ("otherwise", BLOCK));
    DRIVE_LOOP = "drive", TYPE, IDENTIFIER, "on", "(", DRIVE_EXPRESSION, ",", DRIVE_EXPRESSION, ")", BLOCK;
    VARDEC = TYPE, IDENTIFIER, (λ | ("is", GENERAL_EXPRESSION));
    PLAYUNTIL_LOOP = "playuntil", BOOLEAN_EXPRESSION, BLOCK;
    BLOCK = "{", { STATEMENT }, "}";
    DRIVE_EXPRESSION = IDENTIFIER | EXPRESSION;

    GENERAL_EXPRESSION = PLAY_EXPRESSION | BOOLEAN_EXPRESSION;

    PLAY_EXPRESSION = "{", PLAY_DEFINITION, {",", PLAY_DEFINITION}, "}";
    PLAY_DEFINITION = POSITION, ":", STRING;

    BOOLEAN_EXPRESSION = BOOLEAN_TERM, {"or", BOOLEAN_TERM}; 
    BOOLEAN_TERM = RELATIVE_EXPRESSION, {"and", RELATIVE_EXPRESSION}; 
    RELATIVE_EXPRESSION = EXPRESSION, {("equals" | ">" | "<"), EXPRESSION}; 

    EXPRESSION = TERM, { ("+" | "-"), TERM } ;
    TERM = FACTOR, { ("*" | "/"), FACTOR } ;
    FACTOR = (("+" | "-" | "not", ">>"), FACTOR) | NUMBER | STRING | ("(", BOOLEAN_EXPRESSION, ")") | IDENTIFIER | ("signal", "(", ")") ;

    IDENTIFIER = LETTER, { LETTER | DIGIT | "_" } ;
    TYPE = "athlete" | "play" | "number" | "down" | "empty";
    POSITION = "QB" | "WR" | "TE" | "RB" | "FB" | "OL" | "DL" | "LB" | "CB" | "S" | "K" | "P";


    STRING = """, { LETTER }, """;
    NUMBER = DIGIT, { DIGIT } ;
    LETTER = ( a | ... | z | A | ... | Z ) ;
    DIGIT = ( 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 ) ;