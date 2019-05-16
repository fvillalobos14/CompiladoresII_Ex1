%option noyywrap
%option reentrant

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #include <fstream>
    #include "expr_lexer.h"

    #define YY_EXTRA_TYPE std::istream *
    #define YY_DECL Token ExprLexer::_getNextToken(yyscan_t yyscanner)
    #define YY_INPUT(buf,result,max_size) \
    do { \
        std::istream * in = yyget_extra(yyscanner); \
        in->read(buf,max_size); \
        result = in->gcount(); \
    }while(0);

    int counter = 0;
%}

%x lncmnt
%x blkcmnt

%%

[ \t\r\n] { }
"+" { return makeToken(yytext,yyleng,Token::OpAdd); }
"-" { return makeToken(yytext,yyleng,Token::OpSub); }
"(" { return makeToken(yytext,yyleng,Token::OpenPar); }
")" { return makeToken(yytext,yyleng,Token::ClosePar); }
";" { return makeToken(yytext,yyleng,Token::Semicolon); }
[0-9.]* { return makeToken(yytext,yyleng,Token::Num); }
[a-zA-Z_0-9]+ { return makeToken(yytext,yyleng,Token::Id); }

"--" { BEGIN(lncmnt); }

<lncmnt>"\n" { BEGIN(INITIAL); }
<lncmnt>. { }

"(*" { counter++; BEGIN(blkcmnt); }

<blkcmnt>"*)" { 
    --counter;
    if(counter == 0){
        BEGIN(INITIAL);
    }else{
        BEGIN(blkcmnt);
    }
 }

<blkcmnt>. { }

. { }

<<EOF>> { return makeToken(yytext,yyleng,Token::Eof); }

%%

ExprLexer::ExprLexer(std::istream &in) : in(&in){
    yylex_init_extra(&in,&yyscanner);
}

ExprLexer::~ExprLexer(){
    yylex_destroy(yyscanner);
}