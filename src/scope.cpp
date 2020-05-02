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

static void scope_tuple_expr(TupleExpr *expr) {
    for (Expr *val : expr->vals)
        scope_expr(val);
}

static void scope_call_expr(CallExpr *expr) {
    scope_expr(expr->val);
    scope_tuple_expr(expr->args);
}

static void scope_identifier_expr(IdentifierExpr *expr) {
    string id = expr->val.text;
    if (!scope_levels[0].count(id)) {
        scope_levels[0][id] = Data(DATA_SEGMENT, id);
    }
}

static void scope_expr(Expr *expr) {
    if (expr->type == BINARYEXPR) scope_binary_expr((BinaryExpr*) expr);
    else if (expr->type == UNARYEXPR) scope_unary_expr((UnaryExpr*) expr);
    else if (expr->type == REALEXPR) scope_real_expr((RealExpr*) expr);
    else if (expr->type == IDENTIFIEREXPR) scope_identifier_expr((IdentifierExpr*) expr);
    else if (expr->type == CALLEXPR) scope_call_expr((CallExpr*) expr);
    else {
        log_error("unexpected expr type");
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
    scope_levels[0]["write"] = Data(DATA_SEGMENT, "write", new Var(CONSTRUCTION, (uint64_t) &ero_write));
    scope_stmts(tree);
    return scope_levels;
}
