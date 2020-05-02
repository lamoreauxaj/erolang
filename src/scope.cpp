#include "scope.h"

static map<int, map<string, Data>> scope_levels;

static void scope_expr(Expr *expr);

static void scope_binary_expr(BinaryExpr *expr) {
    scope_expr(expr->left);
    scope_expr(expr->right);
}

static void scope_unary_expr(UnaryExpr *expr) {

}

static void scope_real_expr(RealExpr *expr) {

}

static void scope_identifier_expr(IdentifierExpr *expr) {
    string id = expr->val.text;
    if (!scope_levels[0].count(id)) {
        scope_levels[0][id] = Data(DATA_SEGMENT, "v_" + id);
    }
}

static void scope_expr(Expr *expr) {
    if (expr->type == BINARYEXPR) scope_binary_expr((BinaryExpr*) expr);
    else if (expr->type == UNARYEXPR) scope_unary_expr((UnaryExpr*) expr);
    else if (expr->type == REALEXPR) scope_real_expr((RealExpr*) expr);
    else if (expr->type == IDENTIFIEREXPR) scope_identifier_expr((IdentifierExpr*) expr);
    else {
        log_error("unexpected expresssion type");
        return;
    }
}

static void scope_while_stmt(WhileStmt *stmt) {

}

static void scope_if_stmt(IfStmt *stmt) {

}

static void scope_expr_stmt(ExprStmt *stmt) {
    scope_expr(stmt->expr);
}

static void scope_stmt(Stmt *stmt) {
    if (stmt->type == EXPRSTMT) scope_expr_stmt((ExprStmt*) stmt);
    else if (stmt->type == IFSTMT) scope_if_stmt((IfStmt*) stmt);
    else if (stmt->type == WHILESTMT) scope_while_stmt((WhileStmt*) stmt);
    else {
        log_error("unexpected statement type");
        return;
    }
}

static void scope_stmts(Stmts *stmts) {
    for (Stmt *stmt : stmts->stmts)
        scope_stmt(stmt);
}

map<int, map<string, Data>> scope_variables(Stmts *tree) {
    scope_stmts(tree);
    return scope_levels;
}
