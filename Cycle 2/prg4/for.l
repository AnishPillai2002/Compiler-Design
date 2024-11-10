%{ 
#include "for.tab.h"
%} 
 
%% 
for return FOR; 
[\(\)] return PARANTHESIS; 
[a-zA-Z0-9]* return OPERAND; 
"="|"<"|">"|">="|"<="|"=="|"++"|"--" return OPERATOR; 
\; return SEMICOLON; 
, return COMMA; 
\n return NEWLINE; 
[ \t]+           ;               // Ignore whitespace
. ; 
%% 

int yywrap(){
    return 1;
}