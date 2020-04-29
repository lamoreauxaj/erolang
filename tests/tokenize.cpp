#include <string>
#include "gtest/gtest.h"
#include "lexer.h"
using namespace std;

void checkTokens(vector<Token> &tokens, vector<Token> &exp) {
    ASSERT_EQ(tokens.size(), exp.size());
    for (int i = 0; i < tokens.size(); i++) {
        ASSERT_EQ(tokens[i].type, exp[i].type);
        ASSERT_EQ(tokens[i].text, exp[i].text);
    }
}

TEST(tokenize1, assignment1) {
    string program = "a = 1.0\n";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::IDENTIFIER, "a"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::REAL, "1.0"),
        Token(TokenType::NEWLINE, "\n")
    };
    checkTokens(tokens, exp);
}

TEST(tokenize2, assignment2) {
    string program = "a = 2\nb = .001\n";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::IDENTIFIER, "a"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::REAL, "2"),
        Token(TokenType::NEWLINE, "\n"),
        Token(TokenType::IDENTIFIER, "b"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::REAL, ".001"),
        Token(TokenType::NEWLINE, "\n")
    };
    checkTokens(tokens, exp);
}

TEST(tokenize3, assignment3) {
    string program = "c= 2\n e =.5\n f=3.14\ng=1.4e5\n";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::IDENTIFIER, "c"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::REAL, "2"),
        Token(TokenType::NEWLINE, "\n"),
        Token(TokenType::IDENTIFIER, "e"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::REAL, ".5"),
        Token(TokenType::NEWLINE, "\n"),
        Token(TokenType::IDENTIFIER, "f"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::REAL, "3.14"),
        Token(TokenType::NEWLINE, "\n"),
        Token(TokenType::IDENTIFIER, "g"),
        Token(TokenType::ASSIGN, "="),
        Token(TokenType::REAL, "1.4e5"),
        Token(TokenType::NEWLINE, "\n")
    };
    checkTokens(tokens, exp);
}

TEST(tokenize4, comma1) {
    string program = "a, b , c";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::IDENTIFIER, "a"),
        Token(TokenType::COMMA, ","),
        Token(TokenType::IDENTIFIER, "b"),
        Token(TokenType::COMMA, ","),
        Token(TokenType::IDENTIFIER, "c")
    };
    checkTokens(tokens, exp);
}

TEST(tokenize5 ,comma2) {
    string program = "a,b,c\n , d e,f\n";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::IDENTIFIER, "a"),
        Token(TokenType::COMMA, ","),
        Token(TokenType::IDENTIFIER, "b"),
        Token(TokenType::COMMA, ","),
        Token(TokenType::IDENTIFIER, "c"),
        Token(TokenType::NEWLINE, "\n"),
        Token(TokenType::COMMA, ","),
        Token(TokenType::IDENTIFIER, "d"),
        Token(TokenType::IDENTIFIER, "e"),
        Token(TokenType::COMMA, ","),
        Token(TokenType::IDENTIFIER, "f"),
        Token(TokenType::NEWLINE, "\n")
    };
    checkTokens(tokens, exp);
}

TEST(tokenize6, singleComment1) {
    string program = "a,b,c #i like cows\n d,e,f#moo moo  moo!\n";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::IDENTIFIER, "a"),
        Token(TokenType::COMMA, ","),
        Token(TokenType::IDENTIFIER, "b"),
        Token(TokenType::COMMA, ","),
        Token(TokenType::IDENTIFIER, "c"),
        Token(TokenType::SINGLE_COMMENT, "i like cows"),
        Token(TokenType::NEWLINE, "\n"),
        Token(TokenType::IDENTIFIER, "d"),
        Token(TokenType::COMMA, ","),
        Token(TokenType::IDENTIFIER, "e"),
        Token(TokenType::COMMA, ","),
        Token(TokenType::IDENTIFIER, "f"),
        Token(TokenType::SINGLE_COMMENT, "moo moo  moo!"),
        Token(TokenType::NEWLINE, "\n")
    };
    checkTokens(tokens, exp);
}

TEST(tokenize7, multicomment1) {
    string program = "a,b,c ##hi aaron, stop \njudging my unit\n tests\n## d,ef #i like cookies";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::IDENTIFIER, "a"),
        Token(TokenType::COMMA, ","),
        Token(TokenType::IDENTIFIER, "b"),
        Token(TokenType::COMMA, ","),
        Token(TokenType::IDENTIFIER, "c"),
        Token(TokenType::MULTI_COMMENT, "hi aaron, stop \njudging my unit\n tests\n"),
        Token(TokenType::IDENTIFIER, "d"),
        Token(TokenType::COMMA, ","),
        Token(TokenType::IDENTIFIER, "ef"),
        Token(TokenType::SINGLE_COMMENT, "i like cookies")
    };
    checkTokens(tokens, exp);
}

TEST(tokenize8, is_keyword1) {
    string program = "tis is yis";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::IDENTIFIER, "tis"),
        Token(TokenType::IS, "is"),
        Token(TokenType::IDENTIFIER, "yis")
    };
    checkTokens(tokens, exp);
}

TEST(tokenize9, if_keyword1) {
    string program = "tif if yif";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::IDENTIFIER, "tif"),
        Token(TokenType::IF, "if"),
        Token(TokenType::IDENTIFIER, "yif")
    };
    checkTokens(tokens, exp);
}

TEST(tokenize10, in_keyword1) {
    string program = "tin in yin";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::IDENTIFIER, "tin"),
        Token(TokenType::IN, "in"),
        Token(TokenType::IDENTIFIER, "yin")
    };
    checkTokens(tokens, exp);
}

TEST(tokenize11, while_keyword1) {
    string program = "while xyzwhile";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::WHILE, "while"),
        Token(TokenType::IDENTIFIER, "xyzwhile")
    };
    checkTokens(tokens, exp);
}

TEST(tokenize12, import_keyword1) {
    string program = "aimportb import";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::IDENTIFIER, "aimportb"),
        Token(TokenType::IMPORT, "import")
    };
    checkTokens(tokens, exp);
}

TEST(tokenize13, or_keyword1) {
    string program = "nor is the only or";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::IDENTIFIER, "nor"),
        Token(TokenType::IS, "is"),
        Token(TokenType::IDENTIFIER, "the"),
        Token(TokenType::IDENTIFIER, "only"),
        Token(TokenType::OR, "or")
    };
    checkTokens(tokens, exp);
}

TEST(tokenize14, and_keyword1) {
    string program = "nand is the only and";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::IDENTIFIER, "nand"),
        Token(TokenType::IS, "is"),
        Token(TokenType::IDENTIFIER, "the"),
        Token(TokenType::IDENTIFIER, "only"),
        Token(TokenType::AND, "and")
    };
    checkTokens(tokens, exp);
}

TEST(tokenize15, not_keyword1) {
    string program = "nnot not";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::IDENTIFIER, "nnot"),
        Token(TokenType::NOT, "not")
    };
    checkTokens(tokens, exp);
}

TEST(tokenize16, else_keyword1) {
    string program = "elsee else";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp =  {
        Token(TokenType::IDENTIFIER, "elsee"),
        Token(TokenType::ELSE, "else")
    };
    checkTokens(tokens, exp);
}