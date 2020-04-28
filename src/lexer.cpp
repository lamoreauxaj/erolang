#include <lexer.h>
#include <string>
#include <vector>

string& programText;
int curIndex;
vector<Token> tokens;

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
    Token ret;

    while (curIndex < programText.length() & isspace(programText[curIndex]) & programText[curIndex] != '\n') {
        curIndex++;
    }
}

vector<Token> tokenize(string& program) {
    programText = program;

    while (curIndex < programText.length()) {
        Token t = next_token();
        tokens.push_back(t);
        curIndex = t.end + 1;
    }

    return tokens;
}