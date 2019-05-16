#ifndef _LEXER_H
#define _LEXER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using TokenInfo = std::pair<int, double>;

class ExprLexer {
public:
    ExprLexer(const std::vector<TokenInfo>& tklst): tklist(tklst) {
        it = tklist.begin();
    }

    int getNextToken(double *yylval) {
        if (it == tklist.end()) {
            return 0;
        }
        int tk = it->first;
        *yylval = it->second;
        it++;
        
        return tk;
    }

private:
    std::vector<TokenInfo> tklist;
    std::vector<TokenInfo>::iterator it;
};
#endif
