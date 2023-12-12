# NFLang

Programming language created to sketch Football plays and strategies.


## Syntax Diagram

![SyntaxDiagram](SyntaxDiagram.svg)

## EBNF

    PROGRAM = { STATEMENT };

    STATEMENT = ( λ | ASSIGNMENT | CALL | WHEN_CONDITIONAL | DRIVE_LOOP | VARDEC | FUNCTION_DECLARATION | PLAYUNTIL_LOOP), "\n" ;

    FUNCTION_STATEMENT = ( λ | ASSIGNMENT | CALL | FUNCTION_WHEN_CONDITIONAL | FUNCTION_DRIVE_LOOP | VARDEC | RESULT | FUNCTION_PLAYUNTIL_LOOP), "\n" ;

    BLOCK = "{", { STATEMENT }, "}";
    FUNCTION_BLOCK = "{", { FUNCTION_STATEMENT }, "}";

    FUNCTION_DECLARATION = "action", TYPE, IDENTIFIER, "(", (λ | FUNCTION_DECLARATION_ARGUMENTS) ")", FUNCTION_BLOCK, "\n";
    FUNCTION_DECLARATION_ARGUMENTS = TYPE, IDENTIFIER {",", TYPE, IDENTIFIER};

    RESULT = "result", GENERAL_EXPRESSION;

    WHEN_CONDITIONAL = "when", BOOLEAN_EXPRESSION, "then", BLOCK, (λ | ("otherwise", BLOCK));
    FUNCTION_WHEN_CONDITIONAL = "when", BOOLEAN_EXPRESSION, "then", FUNCTION_BLOCK, (λ | ("otherwise", FUNCTION_BLOCK));

    DRIVE_LOOP = "drive", TYPE, IDENTIFIER, "on", "(", BOOLEAN_EXPRESSION, ",", BOOLEAN_EXPRESSION, ")", BLOCK;
    FUNCTION_DRIVE_LOOP = "drive", TYPE, IDENTIFIER, "on", "(", BOOLEAN_EXPRESSION, ",", BOOLEAN_EXPRESSION, ")", FUNCTION_BLOCK;

    VARDEC = TYPE, IDENTIFIER, (λ | ("is", GENERAL_EXPRESSION));

    ASSIGNMENT = IDENTIFIER, ("is", GENERAL_EXPRESSION) | ACTION_CALL_ARGUMENTS | (".", POSITION, "is", BOOLEAN_EXPRESSION) ;
    ACTION_CALL_ARGUMENTS = "(", λ | (GENERAL_EXPRESSION, {",", GENERAL_EXPRESSION}) ")";

    CALL = "call", "(", BOOLEAN_EXPRESSION, ")" ;
    PLAYUNTIL_LOOP = "playuntil", BOOLEAN_EXPRESSION, BLOCK;

    GENERAL_EXPRESSION = PLAY_EXPRESSION | BOOLEAN_EXPRESSION;

    PLAY_EXPRESSION = "{", λ | (PLAY_DEFINITION, {",", PLAY_DEFINITION}), "}";
    PLAY_DEFINITION = POSITION, ":", BOOLEAN_EXPRESSION;

    BOOLEAN_EXPRESSION = BOOLEAN_TERM, {"or", BOOLEAN_TERM}; 
    BOOLEAN_TERM = RELATIVE_EXPRESSION, {"and", RELATIVE_EXPRESSION}; 
    RELATIVE_EXPRESSION = EXPRESSION, {("equals" | ">" | "<"), EXPRESSION}; 

    EXPRESSION = TERM, { ("+" | "-"), TERM } ;
    TERM = FACTOR, { ("*" | "/"), FACTOR } ;
    FACTOR = (("+" | "-" | "not", ">>"), FACTOR) | NUMBER | STRING | DOWN | ("(", BOOLEAN_EXPRESSION, ")") | IDENTIFIER, (λ | ACTION_CALL_ARGUMENTS | (".", POSITION))  | ("signal", "(", ")") ;

    IDENTIFIER = LETTER, { LETTER | DIGIT | "_" } ;
    TYPE = "athlete" | "play" | "number" | "down" | "empty";
    DOWN = "firstdown" | "seconddown" | "thirddown" | "fourthdown" | "toondowns";
    POSITION = "QB" | "WR" | "TE" | "RB" | "FB" | "OL" | "DL" | "LB" | "CB" | "S" | "K" | "P";


    STRING = """, { LETTER }, """;
    NUMBER = DIGIT, { DIGIT } ;
    LETTER = ( a | ... | z | A | ... | Z ) ;
    DIGIT = ( 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 ) ;