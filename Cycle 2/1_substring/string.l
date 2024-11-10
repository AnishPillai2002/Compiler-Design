/*•	Write a lex program to recognize all strings which does not contain first four characters of your name as a substring.*/

%{
#include <stdio.h>
#include<string.h>

void check(char *string,char *name){

    if(strstr(string,name)==NULL){
        printf("Valid String\n");
    }else{
        printf("Invalid String\n");
    }
}


%}

%%
[A-Za-z]+  { check(yytext,"anish"); } 

%%

int main() {
    printf("Enter the string: ");
    
    // Call yylex to scan input and apply rules
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
