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

TEST(lexer, assignment1) {
    string program = "a = 1.0\n";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::IDENTIFIER, "a"),
        Token(TokenType::EQUALS, "="),
        Token(TokenType::REAL, "1.0")
    };
    checkTokens(tokens, exp);
}

TEST(lexer, assignment2) {
    string program = "a = 2\nb = .001\n";
    vector<Token> tokens = tokenize(program);
    vector<Token> exp = {
        Token(TokenType::IDENTIFIER, "a"),
        Token(TokenType::EQUALS, "="),
        Token(TokenType::REAL, "1.0"),
        Token(TokenType::NEWLINE, "\n"),
        Token(TokenType::IDENTIFIER, "b"),
        Token(TokenType::EQUALS, "="),
        Token(TokenType::REAL, ".001"),
        Token(TokenType::NEWLINE, "\n"),
    };
    checkTokens(tokens, exp);
}
