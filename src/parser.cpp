#include "parser.h"
using namespace std;

vector<Token> tokens;
int pos;

bool eof() {
    return pos >= tokens.size();
}

void advance() {
    if (!eof())
        pos++;
}

bool match(TokenType type) {
    if (!eof() && tokens[pos].type == type) {
        pos++
        return true;
    }
    return false;
}

bool parse_statements(Stmts &res) {
    vector<Stmt> stmts;
    while (true) {
    }
}

Stmts parse(vector<Token> &tok) {
    tokens = tok;
    Stmts res;
    parse_statements()
}