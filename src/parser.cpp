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
Expr *parse_expr();

Expr *parse_primary_expr() {
    Token val;
    if (consume(REAL, val)) return new RealExpr(val);
    else if (consume(IDENTIFIER, val)) return new IdentifierExpr(val);
    else if (peek(LEFT_PAREN)) {
        Expr *expr = parse_expr();
        if (peek(COMMA)) {
            vector<Expr*> tuple = {expr};
            while (!peek(RIGHT_PAREN)) {
                if (!consume(COMMA)) {
                    log_error("expected comma");
                    return nullptr;
                }
                Expr *expr = parse_expr();
                if (expr)
                    tuple.push_back(expr);
            }
            return new TupleExpr(tuple);
        }
        else {
            if (!consume(RIGHT_PAREN)) {
                log_error("expected right paren");
                return nullptr;
            }
            return new GroupExpr(expr);
        }
    }
    else {
        Expr *expr = parse_expr();
        if (!expr) return nullptr;
        if (consume(LEFT_BRACKET)) {
            Expr *index = parse_expr();
            if (!index) {
                log_error("expected index");
                return nullptr;
            }
            if (!consume(RIGHT_BRACKET)) {
                log_error("expected right bracket");
                return nullptr;
            }
            return new IndexExpr(expr, index);
        }
        else {
            if (!consume(LEFT_PAREN)) {
                log_error("expected left paren");
                return nullptr;
            }
            vector<Expr*> args;
            while (!peek(RIGHT_PAREN)) {
                Expr *arg = parse_expr();
                if (!arg) {
                    log_error("expected arg");
                    return nullptr;
                }
                args.push_back(arg);
            }
            if (!consume(RIGHT_PAREN)) {
                log_error("expected right paren");
                return nullptr;
            }
            return new CallExpr(expr, args);
        }
    }
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
            Token xop;
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
