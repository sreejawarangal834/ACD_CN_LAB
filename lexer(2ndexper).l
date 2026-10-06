%{
#include <stdio.h>
%}

%%

"int"|"float"|"char"|"if"|"else"|"while"|"for"|"return"
        { printf("KEYWORD     : %s\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*
        { printf("IDENTIFIER  : %s\n", yytext); }

[0-9]+
        { printf("NUMBER      : %s\n", yytext); }

"=="|"!="|"<="|">="|"="|"+"|"-"|"*"|"/"|"<"|">"
        { printf("OPERATOR    : %s\n", yytext); }

"("|")"|"{"|"}"|";"|","
        { printf("SEPARATOR   : %s\n", yytext); }

"//".*
        { /* Ignore comments */ }

[ \t\n]+
        { /* Ignore whitespace */ }

.
        { printf("UNKNOWN     : %s\n", yytext);      }

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
/*
v1 lexer.l
flex lexer.l
 gcc lex.yy.c -o lexer 
./lexer  */