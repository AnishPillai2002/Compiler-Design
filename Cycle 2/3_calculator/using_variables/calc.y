%{
    int values[26]; // values in variable
%}

%token SEMI ASSIGN VAR NUMBER;
%right ASSIGN;

%%
P: P S |;
S: VAR ASSIGN E SEMI {values[$1] = $3;}
| VAR SEMI {printf("%d",values[$1]);};
E : E '+' E {$$ = $1 + $3;}
|E '-' E {$$ = $1 - $3;}
|E '*' E {$$ = $1 * $3;}
|E '%' E {$$ = $1 % $3;}
|VAR {$$ = values[$1];}
|NUMBER;

%%

int main(){
    yyparse();
}

int yyerror(){
    printf("Synatx Error");
    return 0;
}
