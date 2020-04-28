#include <lexer.h>
#include <string>
#include <vector>

TokenType char_type(char c) {
    switch (c) {
        case '\n': return NEWLINE;
        case '\\': return BACKSLASH;
        case ';': return SEMICOLON;
        case '(': return LEFT_PAREN;
        case ')': return RIGHT_PAREN;
        case '[': return LEFT_BRACKET;
        case ']': return RIGHT_BRACKET;
        case '{': return LEFT_BRACE;
        case '}': return RIGHT_BRACE;
        case '=': return EQUALS;
        case '#': return SINGLE_COMMENT;
        case ',': return COMMA;
        case '-': return APPLY;  
        default: return IDENTIFIER;
    }
}

bool one_char(TokenType t) {
    return (t == NEWLINE) | (t == BACKSLASH) | (t == SEMICOLON) | (t == LEFT_PAREN) | (t == RIGHT_PAREN) | 
        (t == LEFT_BRACKET) | (t == RIGHT_BRACKET) | (t == LEFT_BRACE) | (t == RIGHT_BRACE) | (t == EQUALS) | (t == COMMA);
}

bool is_keyword() {

}

Token next_token() {

}

vector<Token> tokenize(string program) {
    vector<Token> tokens;


}