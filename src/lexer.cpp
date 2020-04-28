#include <lexer.h>
#include <string>
#include <log.h>
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
    return (t == NEWLINE) || (t == BACKSLASH) || (t == SEMICOLON) || (t == LEFT_PAREN) || (t == RIGHT_PAREN) || 
        (t == LEFT_BRACKET) || (t == RIGHT_BRACKET) || (t == LEFT_BRACE) || (t == RIGHT_BRACE) || (t == EQUALS) || (t == COMMA);
}

bool is_keyword() {

    return false;
}

Token next_token() {
    TokenType next_type;
    string next_text = "";
    int next_start = -1;
    int next_end = -1;

    while (curIndex < program.length() && isspace(program[curIndex]) && program[curIndex] != '\n')
        curIndex++;

    TokenType t = char_type(program[curIndex]);
    if (one_char(t))
        return Token(t, program.substr(curIndex, 1), curIndex, curIndex);

    next_start = curIndex;
    
    // handle comments
    if (t == SINGLE_COMMENT) {
        // multi comment
        if (curIndex + 1 < program.length() && program[curIndex + 1] == '#') {
            curIndex++;
            while (curIndex + 1 < program.length()) {
                if (program[curIndex + 1] == '#') {
                    if (curIndex + 2 < program.length() && program[curIndex + 2] == '#') {
                        next_end = curIndex + 2;
                        break;
                    } else {
                        next_text.push_back(program[curIndex + 1]);
                    }
                } else {
                    next_text.push_back(program[curIndex + 1]);
                }

                curIndex++;
            }

            if (next_end == -1)
                log_error("multicomment does not end properly", next_start, -1);
            
            return Token(MULTI_COMMENT, next_text, next_start, next_end);
        } 
        // single comment
        else {
            while (++curIndex < program.length()) {
                if (program[curIndex] == '\n') {
                    break;
                } else {
                    next_text.push_back(program[curIndex]);
                }
            }

            next_end = curIndex;
            return Token(SINGLE_COMMENT, next_text, next_start, next_end);
        }
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