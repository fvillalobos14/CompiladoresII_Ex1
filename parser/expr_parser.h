#ifndef _EXPR_PARSER_H
#define _EXPR_PARSER_H

#include <stdio.h>
#include <utility>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include "expr_lexer.h"
#include "expr_tokens.h"

class ExprParser {
    public:
        ExprParser(ExprLexer & lex) : lexer(lex) {};
        ~ExprParser() {};
        int parse();

        int getExprCount(){
            return map.size();
        }

        double getExprValue(int index){
            return map[index];
        }

        void yyerror(const char * msg);

    private:
        ExprLexer & lexer;
        std::vector<double> map;

};

#endif
