%{
    #include "y.tab.h"
    #include <stdlib.h>
    extern int yylval;
%}


%%
[0-9]+ {
    yylval = atoi(yytext);
    return NUMBER;};
";" return SEMI;
= return ASSIGN;
[a-z] {
    yylval = yytext[0]-26;
    return VAR;};
"\n"|" " ;
[+-/%] {return yytext[0];};
. ;
%%

int yywrap(){
    return 0;
}

