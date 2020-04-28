#include <lexer.h>
#include <string>
#include <vector>

using namespace std;

string& program;
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

    return false;
}

Token next_token() {
    TokenType next_type;
    string next_text;
    int next_start;
    int next_end;

    while (curIndex < program.length() & isspace(program[curIndex]) & program[curIndex] != '\n')
        curIndex++;

    next_start = curIndex;

    TokenType t = char_type(program[curIndex]);
    
    if (one_char(t)) {
        struct Token ret = Token(t, "abcd", next_start, next_end);
        return ret;
    }
    

}

vector<Token> tokenize(string& programText) {
    program = programText;

    while (curIndex < programText.length()) {
        Token t = next_token();
        tokens.push_back(t);
        curIndex = t.end + 1;
    }

    return tokens;
}