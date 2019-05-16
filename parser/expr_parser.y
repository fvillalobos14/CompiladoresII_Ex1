%pure-parser

%code requires{
    using YYSTYPE = double;
    #define YYSTYPE_IS_DECLARED 1
}

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <vector>
    #include "expr_parser.h"

    #define YYERROR_VERBOSE 1

    #define yylex(arg) lexer.getNextToken(arg)
    #define yyparse(x) ExprParser::parse()

    void ExprParser::yyerror(const char * msg){
        std::cout << msg << std::endl;
    }
%}

%token NUMBER
%token END 0 "END OF FILE"

%left "*" "/"
%left "+" "-"

%%

input: input expr ";" { map.push_back($2); }
    | %empty { }
    ;

expr:   expr "+" term { $$ = $1 + $3; }
    |   expr "-" term { $$ = $1 - $3; }
    |   term    { $$ = $1; }   
    ;

term:   term "*" factor { $$ = $1 * $3; }
    |   term "/" factor { $$ = $1 / $3; }
    |   factor { $$ = $1; }
    ;

factor: NUMBER { $$ = $1; }
    |   "(" expr ")" { $$ = $2; }
    ;