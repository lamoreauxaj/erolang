#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <log.h>

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
    ASSIGN,         // =
    SINGLE_COMMENT, // # text
    MULTI_COMMENT,  // ## text\ntext ##
    COMMA,          // ,
    IF,             // if
    ELSE,           // else
    IS,             // is
    REAL,           // any floating point value
    APPLY,          // -> operator
    // everything after this point is optional to implement if we have time / want
    // these features
    WHILE, // while
    PLUS, // +
    PLUS_EQUALS, // +=
    MINUS, // -
    MINUS_EQUALS, // -=
    TIMES, // *
    TIMES_EQUALS, // *=
    DIVIDE, // /
    DIVIDE_EQUALS, // /=
    IDIVIDE, // //
    IDIVIDE_EQUALS, // //=
    POWER, // ^
    POWER_EQUALS, // ^=
    MOD, // % 
    MOD_EQUALS, // %=
    NOT, // ! or not
    XOR, // ^^
    XOR_EQUALS, // ^^=
    AND, // and or &&
    AND_EQUALS, // &&=
    OR, // or or ||
    OR_EQUALS, // ||=
    EQUALS, // ==
    NOT_EQUALS, // !=
    LESS, // <
    GREATER, // >
    LESS_OR_EQUAL, // <=
    GREATER_OR_EQUAL, // >=
    SLICE, // :
    IN, // in
    STRING, // "text", 'test', '''multiple lines''', """multiple lines""" - can contain '\n', '\t', '\x##', \' \"
    IMPORT, // import 
};

struct Token {
    TokenType type;
    string text;
    int start, end;

    Token() {}
    Token(TokenType type, string text) : type(type), text(text) {}
    Token(TokenType type, string text, int start, int end) : type(type), text(text), start(start), end(end) {}
};

vector<Token> tokenize(string& program);

#endif