%{
#include <stdio.h>
%}

%%

"int"|"float"|"char"|"double"|"if"|"else"|"while"|"for"|"return"|"void" {
    printf("Keyword: %s\n", yytext);
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("Identifier: %s\n", yytext);
}

[0-9]+(\.[0-9]+)? {
    printf("Number: %s\n", yytext);
}

"=="|"!="|"<="|">="|"++"|"--" {
    printf("Operator: %s\n", yytext);
}

[+\-*/%=<>] {
    printf("Operator: %s\n", yytext);
}

[(){};,] {
    printf("Special Symbol: %s\n", yytext);
}

[ \t\n]+ {
    /* Ignore whitespace */
}

. {
    printf("Unknown Character: %s\n", yytext);
}

%%

int main()
{
    printf("Enter the source code:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}