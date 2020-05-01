#include "compile.h"

enum DataLocation {
    DATA_SEGMENT, // store global and captured variables
    STACK // all other local variables
};

struct Data {
    DataLocation loc;
    int pos;
};

map<int, map<string, Data>> scope_levels;
queue<Node*> function_queue;

void compile_expr(Expr *expr);

void compile_real_expr(RealExpr *expr) {

}

void compile_unary_expr(UnaryExpr *expr) {

}

void compile_binary_expr(BinaryExpr *expr) {

}

void compile_expr(Expr *expr) {
    if (expr->type == BINARYEXPR) compile_binary_expr((BinaryExpr*) expr);
    else if (expr->type == UNARYEXPR) compile_unary_expr((UnaryExpr*) expr);
    else if (expr->type == REALEXPR) compile_real_expr((RealExpr*) expr);
    else {
        log_error("unknown expr type");
        return;
    }
}

void compile_expr_stmt(ExprStmt *stmt) {
    compile_expr(stmt->expr);
}

void compile_if_stmt(IfStmt *stmt) {

}

void compile_while_stmt(WhileStmt *stmt) {

}

void compile_stmt(Stmt *stmt) {
    if (stmt->type == EXPRSTMT) compile_expr_stmt((ExprStmt*) stmt);
    else if (stmt->type == IFSTMT) compile_if_stmt((IfStmt*) stmt);
    else if (stmt->type == WHILESTMT) compile_while_stmt((WhileStmt*) stmt);
    else {
        log_error("unknown stmt type");
        return;
    }
}

void compile_stmts(Stmts *node) {
    for (Stmt *child : node->stmts) {

    }
}

void compile(Node *tree) {

}
