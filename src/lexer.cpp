#include <lexer.h>

string program;
int curIndex;

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
        case '=': return ASSIGN;
        case '#': return SINGLE_COMMENT;
        case ',': return COMMA;
        case '-': return MINUS;
        case '+': return PLUS;
        case '*': return TIMES;
        case '/': return DIVIDE;
        case ':': return SLICE;
        default: return IDENTIFIER;
    }
}

bool one_char(TokenType t) {
    return (t == NEWLINE) || (t == BACKSLASH) || (t == SEMICOLON) || (t == LEFT_PAREN) || (t == RIGHT_PAREN) || (t == PLUS) ||
        (t == LEFT_BRACKET) || (t == RIGHT_BRACKET) || (t == LEFT_BRACE) || (t == RIGHT_BRACE) || (t == COMMA)
        || (t == TIMES) || (t == DIVIDE) || (t == SLICE);
}

TokenType is_keyword(string s) {
    if (s == "is") return TokenType::IS;
    if (s == "else") return TokenType::ELSE;
    if (s == "if") return TokenType::IF;
    if (s == "in") return TokenType::IN;
    if (s == "while") return TokenType::WHILE;
    if (s == "import") return TokenType::IMPORT;
    if (s == "or") return TokenType::OR;
    if (s == "and") return TokenType::AND;
    if (s == "not") return TokenType::NOT;
    if (s == "construction") return TokenType::CONSTRUCTION;
    return TokenType::IDENTIFIER;
}

bool alpha_num(char c) {
    return isalnum(c) || (c == '_') || (c == '.');
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

            next_end = curIndex - 1;
            return Token(SINGLE_COMMENT, next_text, next_start, next_end);
        }
    }

    if (t == MINUS) {
        if (curIndex + 1 < program.length() && program[curIndex + 1] == '>') {
            return Token(APPLY, "->", curIndex, curIndex + 1);
        } else {
            return Token(MINUS, "-", curIndex, curIndex);
        }
    }

    if (t == ASSIGN) {
        if (curIndex + 1 < program.length() && program[curIndex + 1] == '=') {
            return Token(EQUALS, "==", curIndex, curIndex + 1);
        } else {
            return Token(ASSIGN, "=", curIndex, curIndex);
        }
    }

    if (!alpha_num(program[curIndex]))
        log_error("unrecognized character", curIndex, curIndex);
    
    // IDENTIFIER
    if (isalpha(program[curIndex])) {
        bool validIdentifier = true;
        while (curIndex < program.length() && alpha_num(program[curIndex])) {
            validIdentifier &= !(program[curIndex] == '.');
            next_text.push_back(program[curIndex]);
            curIndex++;
        }

        next_end = curIndex - 1;

        if (!validIdentifier)
            log_error("invalid identifier", next_start, next_end);

        t = is_keyword(next_text);
        return Token(t, next_text, next_start, next_end);
    } 
    // REAL
    else {
        bool validReal = true;
        while (curIndex < program.length() && alpha_num(program[curIndex])) {
            validReal &= program[curIndex] == 'E' || program[curIndex] == 'e' || program[curIndex] == '.' || isdigit(program[curIndex]);
            next_text.push_back(program[curIndex]);
            curIndex++;
        }

        next_end = curIndex - 1;

        if (!validReal)
            log_error("invalid real", next_start, next_end);

        return Token(REAL, next_text, next_start, next_end);
    }
}

vector<Token> tokenize(string& programText) {
    program = programText;
    curIndex = 0;
    vector<Token> tokens;

    while (curIndex < programText.length()) {
        Token t = next_token();
        tokens.push_back(t);
        curIndex = t.end + 1;
    }

    return tokens;
}