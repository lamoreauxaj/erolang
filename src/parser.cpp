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
    Expr *expr = parse_unary_expr();
    if (!expr) return nullptr;
    while (true) {
        Token op;
        if (!consume(POWER, op)) break;
        Expr *right = parse_exponentiation_expr();
        if (!right) {
            log_error("incomplete binary operator");
            return nullptr;
        }
        expr = new BinaryExpr(expr, op, right);
    }
    return expr;
}

Expr *parse_multiplication_expr() {
    Expr *expr = parse_exponentiation_expr();
    if (!expr) return nullptr;
    while (true) {
        Token op;
        if (!consume(DIVIDE, op) && !consume(TIMES, op) && !consume(IDIVIDE, op) && !consume(MOD, op)) break;
        Expr *right = parse_exponentiation_expr();
        if (!right) {
            log_error("incomplete binary operator");
            return nullptr;
        }
        expr = new BinaryExpr(expr, op, right);
    }
    return expr;
}

Expr *parse_addition_expr() {
    Expr *expr = parse_multiplication_expr();
    if (!expr) return nullptr;
    while (true) {
        Token op;
        if (!consume(PLUS, op) && !consume(MINUS, op)) break;
        Expr *right = parse_multiplication_expr(); // left associative operation
        if (!right) {
            log_error("incomplete binary operator");
            return nullptr;
        }
        expr = new BinaryExpr(expr, op, right);
    }
    return expr;
}

Expr *parse_comparision_expr() {
    Expr *expr = parse_addition_expr();
    if (!expr) return nullptr;
    while (true) {
        Token op;
        if (!consume(IS, op) && !consume(EQUALS, op) && !consume(NOT_EQUALS, op) && !consume(IN, op) && !consume(NOT, op)) break;
        if (op.type == NOT) {
            Token xop = NONE;
            if (!consume(IS, xop) && !consume(IN, xop)) break;
            Expr *right = parse_addition_expr();
            if (!right) {
                log_error("incomplete binary operator");
                return nullptr;
            }
            expr = new BinaryExpr(expr, op, xop, right);
        }
        else {
            Expr *right = parse_addition_expr();
            if (!right) {
                log_error("incomplete binary operator");
                return nullptr;
            }
            expr = new BinaryExpr(expr, op, right);
        }
    }
    return expr;
}

Expr *parse_conjunction_expr() {
    Expr *expr = parse_comparision_expr();
    if (!expr) return nullptr;
    while (true) {
        Token op;
        if (!consume(AND, op)) break;
        Expr *right = parse_comparision_expr();
        if (!right) {
            log_error("incomplete binary operator");
            return nullptr;
        }
        expr = new BinaryExpr(expr, op, right);
    }
    return expr;
}

Expr *parse_xdisjunction_expr() {
    Expr *expr = parse_conjunction_expr();
    if (!expr) return nullptr;
    while (true) {
        Token op;
        if (!consume(XOR, op)) break;
        Expr *right = parse_conjunction_expr();
        if (!right) {
            log_error("incomplete binary operator");
            return nullptr;
        }
        expr = new BinaryExpr(expr, op, right);
    }
    return expr;
}

Expr *parse_disjunction_expr() {
    Expr *expr = parse_xdisjunction_expr();
    if (!expr) return nullptr;
    while (true) {
        Token op;
        if (!consume(OR, op)) break;
        Expr *right = parse_xdisjunction_expr();
        if (!right) {
            log_error("incomplete binary operator");
            return nullptr;
        }
        expr = new BinaryExpr(expr, op, right);
    }
    return expr;
}

Expr *parse_assignment_expr() {
    Expr *expr = parse_disjunction_expr();
    if (!expr) return nullptr;
    while (true) {
        Token op;
        if (!consume(ASSIGN, op)) break;
        Expr *right = parse_assignment_expr(); // right associative is recursive
        if (!right) {
            log_error("incomplete binary operator");
            return nullptr;
        }
        expr = new BinaryExpr(expr, op, right);
    }
    return expr;
}

Expr *parse_expr() {
    return parse_assignment_expr();
}

IfStmt *parse_if_stmt() {
    if (!consume(IF)) {
        log_error("missing if token");
        return nullptr;
    }
    if (!consume(LEFT_PAREN)) {
        log_error("missing left paren in if");
        return nullptr;
    }
    Expr *expr = parse_expr();
    if (!expr) {
        return nullptr;
    }
    if (!consume(RIGHT_PAREN)) {
        log_error("missing right paren in if");
        return nullptr;
    }
    if (!consume(LEFT_BRACE)) {
        log_error("missing left brace in if");
        return nullptr;
    }
    Stmts *stmts = parse_statements();
    if (!stmts) {
        return nullptr;
    }
    if (!consume(RIGHT_BRACE)) {
        log_error("missing right brace in if");
        return nullptr;
    }
    return new IfStmt(expr, stmts);
}

WhileStmt *parse_while_stmt() {
    if (!consume(WHILE)) {
        log_error("missing while token");
        return nullptr;
    }
    if (!consume(LEFT_PAREN)) {
        log_error("missing left paren in while");
        return nullptr;
    }
    Expr *expr = parse_expr();
    if (!expr) {
        return nullptr;
    }
    if (!consume(RIGHT_PAREN)) {
        log_error("missing right paren in while");
        return nullptr;
    }
    if (!consume(LEFT_BRACE)) {
        log_error("missing left brace in while");
        return nullptr;
    }
    Stmts *stmts = parse_statements();
    if (!stmts) {
        return nullptr;
    }
    if (!consume(RIGHT_BRACE)) {
        log_error("missing right brace in while");
        return nullptr;
    }
    return new WhileStmt(expr, stmts);
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
