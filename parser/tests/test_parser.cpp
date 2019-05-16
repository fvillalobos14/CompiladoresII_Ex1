#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <vector>
#include "doctest.h"
#include "expr_tokens.h"
#include "expr_parser.h"

std::vector<TokenInfo> test1 = {
    {NUMBER, 45.0},
    {'+', 0},
    {NUMBER, 10.0},
};

std::vector<TokenInfo> test2 = {
    {'(', 0.0},
    {NUMBER, 0.535},
    {'-', 0.0},
    {NUMBER, 0.035},
    {')', 0.0},
    {'*', 0.0},
    {NUMBER, 10.0},
};

std::vector<TokenInfo> test3 = {
    {'(', 0.0},
    {NUMBER, 0.535},
    {'-', 0.0},
    {NUMBER, 0.035},
    {')', 0.0},
    {'*', 0.0},
    {NUMBER, 100.0},
    {';', 0.0},
    {'(', 0.0},
    {NUMBER, 0.4},
    {'+', 0.0},
    {NUMBER, 0.6},
    {')', 0.0},
    {'/', 0.0},
    {NUMBER, 4},
};

TEST_CASE("Add expression") {
    ExprLexer lexer(test1);
    ExprParser parser(lexer);
    
    parser.parse();
    CHECK(parser.getExprCount() == 1);
    CHECK(parser.getExprValue(0) == 55);
}

TEST_CASE("Sub/Mult expression") {
    ExprLexer lexer(test2);
    ExprParser parser(lexer);
    
    parser.parse();
    CHECK(parser.getExprCount() == 1);
    CHECK(parser.getExprValue(0) == 5.0);
}

TEST_CASE("Multiple expressions") {
    ExprLexer lexer(test3);
    ExprParser parser(lexer);
    
    parser.parse();
    CHECK(parser.getExprCount() == 2);
    CHECK(parser.getExprValue(0) == 50.0);
    CHECK(parser.getExprValue(1) == 0.25);
}

