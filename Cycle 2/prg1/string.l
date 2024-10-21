/*•	Write a lex program to recognize all strings which does not contain first four characters of your name as a substring.*/

%{
#include<stdio.h>

//helper method
int check(char *str) {
    
    for(int i=0;str[i]!='\0';i++) {
        if(str[i]=='a' || str[i]=='n' || str[i]=='i' || str[i]=='s') {
            continue;
        }else {
            printf("%c",str[i]);
        }
    }
    printf("\n");
}

%}

%%
[a-zA-Z]+ { check(yytext); }

%%

int main() {
    printf("Enter the code: \n");
    yylex(); // call to invoke lexer, returns token
    return 0;
}

int yywrap(void) {
    return 1;
}