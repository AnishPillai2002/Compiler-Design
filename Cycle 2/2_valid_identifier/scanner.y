%{
#include<stdio.h>
int valid=1;  // To check if the input is valid or not

%}

%token DIGIT LETTER


%%

start : LETTER s

s :     LETTER s

      | DIGIT s  // Digit can be added to the identifier

      |        // Empty string

      ;

%%

int yyerror()

{

    printf("\nIts not a identifier!\n");

    valid=0;

    return 0;

}

int main(){

    printf("\nEnter a name to tested for identifier: ");

    yyparse();

    if(valid){
        printf("\nIt is a identifier!\n");
    }
}
