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

bool does_match(TokenType type) {
    return !eof() && tokens[pos].type == type;
}

bool match(TokenType type, Token &res) {
    if (does_match(type)) {
        res = tokens[pos++];
        return true;
    }
    return false;
}

bool parse_index_expr(IndexExpr &res) {
    return false;
}

bool parse_call_expr(CallExpr &res) {
    return false;
}

bool parse_tuple_expr(TupleExpr &res) {
    return false;
}

bool parse_identifier_expr(IdentifierExpr &res) {
    return false;
}

bool parse_real_expr(RealExpr &res) {
    return false;
}

bool parse_primary_expr(PrimaryExpr &res) {
    return false;
}

bool parse_unary_expr(UnaryExpr &res) {
    return false;
}

bool parse_exponentiation_expr(ExponentiationExpr &res) {
    return false;
}

bool parse_multiplication_expr(MultiplicationExpr &res) {
    return false;
}

bool parse_addition_expr(AdditionExpr &res) {
    return false;
}

bool parse_comparision_expr(ComparisionExpr &res) {
    return false;
}

bool parse_conjunction_expr(ConjunctionExpr &res) {
    return false;
}

bool parse_xdisjunction_expr(XdisjunctionExpr &res) {
    return false;
}

bool parse_disjunction_expr(DisjunctionExpr &res) {
    return false;
}

bool parse_assignment_expr(AssignmentExpr &res) {
    return false;
}

bool parse_expr(Expr &res) {
    return parse_assignment_expr(res);
}

bool parse_if_stmt(IfStmt &res) {
    if (!does_match(IF)) {
        log_error("missing if token");
        return false;
    }
    advance();
    if (!does_match(LEFT_PAREN)) {
        log_error("missing left paren in if");
        return false;
    }
    advance();
    Expr expr;
    if (!parse_expr(expr)) {
        return false;
    }
    if (!does_match(RIGHT_PAREN)) {
        log_error("missing right paren in if");
        return false;
    }
    if (!does_match(LEFT_BRACE)) {
        log_error("missing left brace in if");
        return false;
    }
    Stmts stmts;
    if (!parse_statements(stmts)) {
        return false;
    }
    if (!does_match(RIGHT_BRACE)) {
        log_error("missing right brace in if");
        return false;
    }
    res = IfStmt(expr, stmts);
    return true;
}

bool parse_while_stmt(WhileStmt &res) {
    return false;
}

bool parse_expr_stmt(ExprStmt &res) {
    return false;
}

bool parse_statement(Stmt &res) {
    if (does_match(IF)) {
        IfStmt stmt;
        if (!parse_if_stmt(stmt)) return false;
        res = stmt;
    }
    else if (does_match(WHILE)) {
        WhileStmt stmt;
        if (!parse_while_stmt(stmt)) return false;
        res = stmt;
    }
    else {
        ExprStmt stmt;
        if (!parse_expr_stmt(stmt)) return false;
        res = stmt;
    }
    return true;
}

bool parse_statements(Stmts &res) {
    vector<Stmt> stmts
    while (true) {
        Stmt stmt;
        if (!parse_statement(stmt)) break;
        stmts.push_back(stmt);
    }
    if (!stmts.size()) return false;
    if (!eof()) return false;
    res = stmts;
}

Stmts parse(vector<Token> &tok) {
    tokens = tok;
    Stmts res;
    if (!parse_statements(res)) {
        log_error("unable to parse program");
    }
    return res;
}