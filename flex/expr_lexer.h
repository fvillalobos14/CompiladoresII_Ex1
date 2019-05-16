#ifndef _EXPR_LEXER_H
#define _EXPR_LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using yyscan_t = void * ;

enum class Token{
    Num,
    Id,
    OpAdd,
    OpSub,
    Semicolon,
    OpenPar,
    ClosePar,
    Error,
    Eof
};

class ExprLexer {
    public:
        ExprLexer(std::istream &in);
        ~ExprLexer();

        Token makeToken(char * txt, int len, Token tkn){
            text = std::string(txt,len);
            return tkn;
        }
        Token getNextToken() { return _getNextToken(yyscanner); }
        std::string getText(){ return text; }

    private:
        std::istream * in;
        std::string text;
        yyscan_t yyscanner;
        Token _getNextToken(yyscan_t yyscanner);
};
#endif
