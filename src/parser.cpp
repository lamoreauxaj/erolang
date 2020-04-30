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

bool peek(TokenType type) {
    return !eof() && tokens[pos].type == type;
}

bool peek(TokenType type, Token &res) {
    if (peek(type)) {
        res = tokens[pos];
        return true;
    }
    return false;
}

bool consume(TokenType type) {
    if (peek(type)) {
        pos++;
        return true;
    }
    return false;
}

bool consume(TokenType type, Token &res) {
    if (peek(type)) {
        res = tokens[pos++];
        return true;
    }
    return false;
}

Stmts *parse_statements();

IndexExpr *parse_index_expr() {
    return nullptr;
}

CallExpr *parse_call_expr() {
    return nullptr;
}

TupleExpr *parse_tuple_expr() {
    return nullptr;
}

IdentifierExpr *parse_identifier_expr() {
    Token val;
    if (!consume(IDENTIFIER, val)) return nullptr;
    return new IdentifierExpr(val);
}

RealExpr *parse_real_expr() {
    Token val;
    if (!consume(REAL, val)) return nullptr;
    return new RealExpr(val);
}

Expr *parse_primary_expr() {
    if (peek(REAL)) return parse_real_expr();
    else if (peek(IDENTIFIER)) return parse_identifier_expr();
    else return nullptr;
}

Expr *parse_unary_expr() {
    return parse_primary_expr();
}

Expr *parse_exponentiation_expr() {
    return parse_unary_expr();
}

Expr *parse_multiplication_expr() {
    return parse_exponentiation_expr();
}

Expr *parse_addition_expr() {
    Expr *expr = parse_multiplication_expr();
    if (!expr) return nullptr;
    while (true) {
        Token op;
        if (!consume(PLUS, op) && !consume(MINUS, op)) break;
        Expr *right = parse_multiplication_expr();
        if (!right) break;
        expr = new BinaryExpr(expr, op, right);
    }
    return expr;
}

Expr *parse_comparision_expr() {
    return parse_addition_expr();
}

Expr *parse_conjunction_expr() {
    return parse_comparision_expr();
}

Expr *parse_xdisjunction_expr() {
    return parse_conjunction_expr();
}

Expr *parse_disjunction_expr() {
    return parse_xdisjunction_expr();
}

Expr *parse_assignment_expr() {
    Expr *expr = parse_disjunction_expr();
    if (!expr) return nullptr;
    while (true) {
        Token op;
        if (!consume(ASSIGN, op)) break;
        Expr *right = parse_assignment_expr();
        if (!right) break;
        expr = new BinaryExpr(expr, op, right);
    }
    return expr;
}

Expr *parse_expr() {
    return parse_assignment_expr();
}

IfStmt *parse_if_stmt() {
    if (!peek(IF)) {
        log_error("missing if token");
        return nullptr;
    }
    advance();
    if (!peek(LEFT_PAREN)) {
        log_error("missing left paren in if");
        return nullptr;
    }
    advance();
    Expr *expr = parse_expr();
    if (!expr) {
        return nullptr;
    }
    if (!peek(RIGHT_PAREN)) {
        log_error("missing right paren in if");
        return nullptr;
    }
    if (!peek(LEFT_BRACE)) {
        log_error("missing left brace in if");
        return nullptr;
    }
    Stmts *stmts = parse_statements();
    if (!stmts) {
        return nullptr;
    }
    if (!peek(RIGHT_BRACE)) {
        log_error("missing right brace in if");
        return nullptr;
    }
    return new IfStmt(expr, stmts);
}

WhileStmt *parse_while_stmt() {
    return nullptr;
}

ExprStmt *parse_expr_stmt() {
    Expr *expr = parse_expr();
    if (!expr) return nullptr;
    return new ExprStmt(expr);
}

Stmt *parse_statement() {
    if (peek(IF)) {
        return parse_if_stmt();
    }
    else if (peek(WHILE)) {
        return parse_while_stmt();
    }
    else {
        return parse_expr_stmt();
    }
}

Stmts *parse_statements() {
    vector<Stmt*> stmts;
    while (!eof()) {
        Stmt *stmt = parse_statement();
        if (!stmt) break;
        stmts.push_back(stmt);
        consume(NEWLINE);
    }
    if (!stmts.size()) return nullptr;
    if (!eof()) return nullptr;
    return new Stmts(stmts);
}

Stmts *parse(vector<Token> &tok) {
    tokens = tok;
    pos = 0;
    return parse_statements();
}