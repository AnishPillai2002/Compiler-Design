%{
#include "scanner.tab.h"
%}

%%

[a-zA-Z_][a-zA-Z_0-9]* {return LETTER;} // Return the token for a letter

[0-9] {return DIGIT;} // Return the token for a digit



\n {return 0;} // End of line

%%

int yywrap(){
    return 1;
}