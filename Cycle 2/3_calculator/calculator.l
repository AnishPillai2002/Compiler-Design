%{
#include<stdio.h>
#include "calculator.tab.h"
extern int yylval; // to pass the value of the token to the parser
//yylval global variable is used to pass the 
//semantic value associated with a token from the lexer to the parser
%}



%%

[0-9]+ {
        yylval=atoi(yytext);
        return NUMBER;
       }
[\t] ; // skip tabs
[\n] return 0; // return 0 to indicate the end of the input

. return yytext[0]; // return the character itself

%%

int yywrap(){
    return 1;
}