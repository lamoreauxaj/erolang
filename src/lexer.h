#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <vector>
using namespace std;

enum TokenType {
    IDENTIFIER,
    NEWLINE,        // I have this so we can go back and detect statement boundaries
    BACKSLASH,      // intended to be before newline 
    SEMICOLON,      // ;
    LEFT_PAREN,     // (
    RIGHT_PAREN,    // )
    LEFT_BRACKET,   // [
    RIGHT_BRACKET,  // ]
    LEFT_BRACE,     // {
    RIGHT_BRACE,    // }
    EQUALS,         // =
    SINGLE_COMMENT, // # text
    MULTI_COMMENT,  // ## text\ntext ##
    COMMA,          // ,
    IF,             // if
    IS,             // is
    REAL,           // any floating point value
    APPLY,          // -> operator
    // everything after this point is optional to implement if we have time / want
    // these features
    WHILE,
    PLUS,
    MINUS,
    TIMES,
    DIVIDE,
    IMPORT,
};

struct Token {
    TokenType type;
    string text;
    int line, start, end;
};

vector<Token> tokenize(string program);

#endif