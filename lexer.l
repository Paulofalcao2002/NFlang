%option noyywrap
%{
#include "nodes.h"
#include "parser.tab.h"
#include <string>

#define MAX_STRING_LENGTH 100 // Define a maximum length for strings

char stored_string[MAX_STRING_LENGTH]; // Buffer to store string value

int parse_dynamic_token(char *token_str, int token_type) {
    if (token_type == NUMBER) {
        yylval.number = atoi(token_str); // Store number value
        return NUMBER; // Return number token
    } 

    if (token_type == STRING) {
        strncpy(stored_string, token_str + 1, strlen(token_str) - 2); // Store the string value (excluding quotes)
        stored_string[strlen(token_str) - 2] = '\0'; // Add null terminator
        yylval.stringValue = new string(strdup(stored_string)); // Store the string value in yylval
        return STRING; // Return string token
    }

    // Store the token string (for all the remaining tokens, no transformation is needed)
    yylval.stringValue = new string(token_str); 

    return token_type; 
}
%}

%%
[ \t] ;
"+" {return PLUS;}
"-" {return MINUS;}
"not" {return NOT;}
">>" {return INCREMENT;}
"(" {return L_PARENTHESIS;}
")" {return R_PARENTHESIS;}
"*" {return TIMES;}
"/" {return DIVIDE;}
"equals" {return EQUALS;}
">" {return GREATER_THAN;}
"<" {return LESSER_THAN;}
"and" {return AND;}
"or" {return OR;}
"," {return COMMA;}
":" {return COLON;}
"{" {return L_BRACKET;}
"}" {return R_BRACKET;}
"is" {return IS;}
"when" {return WHEN;}
"then" {return THEN;}
"otherwise" {return OTHERWISE;}
"drive" {return DRIVE;}
"on" {return ON;}
"signal" {return SIGNAL;}
"playuntil" {return PLAY_UNTIL;}
"call" {return CALL;}
"\n" {return BREAK_LINE;}
"action" {return ACTION;}
"result" {return RESULT;}
"athlete" {return parse_dynamic_token(yytext, TYPE);}
"play" {return parse_dynamic_token(yytext, TYPE);}
"number" {return parse_dynamic_token(yytext, TYPE);}
"down" {return parse_dynamic_token(yytext, TYPE);}
"empty" {return parse_dynamic_token(yytext, TYPE);}
"firstdown" {return parse_dynamic_token(yytext, DOWN);}
"seconddown" {return parse_dynamic_token(yytext, DOWN);}
"thirddown" {return parse_dynamic_token(yytext, DOWN);}
"fourthdown" {return parse_dynamic_token(yytext, DOWN);}
"QB" {return parse_dynamic_token(yytext, POSITION);}
"WR" {return parse_dynamic_token(yytext, POSITION);}
"TE" {return parse_dynamic_token(yytext, POSITION);}
"RB" {return parse_dynamic_token(yytext, POSITION);}
"FB" {return parse_dynamic_token(yytext, POSITION);}
"OL" {return parse_dynamic_token(yytext, POSITION);}
"DL" {return parse_dynamic_token(yytext, POSITION);}
"LB" {return parse_dynamic_token(yytext, POSITION);}
"CB" {return parse_dynamic_token(yytext, POSITION);}
"S" {return parse_dynamic_token(yytext, POSITION);}
"K" {return parse_dynamic_token(yytext, POSITION);}
"P" {return parse_dynamic_token(yytext, POSITION);}

[a-zA-Z][_a-zA-Z0-9]* {
    return parse_dynamic_token(yytext, IDENTIFIER);
}

[0-9]+ {
    return parse_dynamic_token(yytext, NUMBER);
}

\"[^\"]*\" {
    return parse_dynamic_token(yytext, STRING);
}


. {
    printf("%s\n", yytext);
    printf("Unknown token !!\n");
}

%%

int main() {
    yyparse();
}
