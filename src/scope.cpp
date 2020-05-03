#include "scope.h"

map<Node*, int> node_scopes;
map<int, map<string, Data>> scope_levels;
map<int, int> parent_scope;
map<int, int> root_scope;
map<int, int> stack_size;

static int scope_counter;
static queue<pair<Stmts*, int>> scope_queue;

static void scope_stmts(Stmts *stmts, int scope);
static void scope_expr(Expr *expr, int scope);

static void resolve_identifier(string id, int scope) {
    int curr = scope;
    while (true) {
        if (scope_levels[curr].count(id)) {
            scope_levels[scope][id] = scope_levels[curr][id];
            break;
        }
        if (!parent_scope.count(curr)) {
            log_error("unable to resolve variable");
            return;
        } 
        curr = parent_scope[curr];
    }
}

static void scope_binary_expr(BinaryExpr *expr, int scope) {
    node_scopes[expr] = scope;
    scope_expr(expr->right, scope);
    if (expr->op.type == ASSIGN) {
        if (expr->left->type != IDENTIFIEREXPR) {
            log_error("expected identifier as lvalue");
            return;
        }
        string id = ((IdentifierExpr*) expr->left)->val.text;
        resolve_identifier(id, scope);
        if (!scope_levels[scope].count(id)) {
            // create new variable
            if (scope == 0) {
                scope_levels[scope][id] = Data(DATA_SEGMENT, id);
            }
            else {
                scope_levels[scope][id] = Data(STACK, stack_size[root_scope[scope]]);
                stack_size[root_scope[scope]] += VAR_SIZE;
            }
        }
    }
    else {
        scope_expr(expr->left, scope);
    }
}

static void scope_unary_expr(UnaryExpr *expr, int scope) {
    node_scopes[expr] = scope;
}

static void scope_real_expr(RealExpr *expr, int scope) {
    node_scopes[expr] = scope;
}

static void scope_tuple_expr(TupleExpr *expr, int scope) {
    node_scopes[expr] = scope;
    for (Expr *val : expr->vals)
        scope_expr(val, scope);
}

static void scope_call_expr(CallExpr *expr, int scope) {
    node_scopes[expr] = scope;
    scope_expr(expr->val, scope);
    scope_tuple_expr(expr->args, scope);
}

static void scope_identifier_expr(IdentifierExpr *expr, int scope) {
    node_scopes[expr] = scope;
    string id = expr->val.text;
    resolve_identifier(id, scope);
    /*
    string id = expr->val.text;
    if (!scope_levels[0].count(id)) {
        scope_levels[0][id] = Data(DATA_SEGMENT, id);
    }
    */
}

static void scope_expr(Expr *expr, int scope) {
    node_scopes[expr] = scope;
    if (expr->type == BINARYEXPR) scope_binary_expr((BinaryExpr*) expr, scope);
    else if (expr->type == UNARYEXPR) scope_unary_expr((UnaryExpr*) expr, scope);
    else if (expr->type == REALEXPR) scope_real_expr((RealExpr*) expr, scope);
    else if (expr->type == IDENTIFIEREXPR) scope_identifier_expr((IdentifierExpr*) expr, scope);
    else if (expr->type == CALLEXPR) scope_call_expr((CallExpr*) expr, scope);
    else {
        log_error("unexpected expr type");
        return;
    }
}

static void scope_while_stmt(WhileStmt *stmt, int scope) {
    node_scopes[stmt] = scope;
    scope_expr(stmt->cond, scope);
    parent_scope[scope_counter + 1] = scope;
    root_scope[scope_counter + 1] = root_scope[scope];
    scope_stmts(stmt->block, ++scope_counter);
}

static void scope_if_stmt(IfStmt *stmt, int scope) {
    node_scopes[stmt] = scope;
    scope_expr(stmt->cond, scope);
    parent_scope[scope_counter + 1] = scope;
    root_scope[scope_counter + 1] = root_scope[scope];
    scope_stmts(stmt->block, ++scope_counter);
}

static void scope_expr_stmt(ExprStmt *stmt, int scope) {
    node_scopes[stmt] = scope;
    scope_expr(stmt->expr, scope);
}

static void scope_stmt(Stmt *stmt, int scope) {
    node_scopes[stmt] = scope;
    if (stmt->type == EXPRSTMT) scope_expr_stmt((ExprStmt*) stmt, scope);
    else if (stmt->type == IFSTMT) scope_if_stmt((IfStmt*) stmt, scope);
    else if (stmt->type == WHILESTMT) scope_while_stmt((WhileStmt*) stmt, scope);
    else {
        log_error("unexpected statement type");
        return;
    }
}

static void scope_stmts(Stmts *stmts, int scope) {
    node_scopes[stmts] = scope;
    stack_size[scope] = 0;
    for (Stmt *stmt : stmts->stmts)
        scope_stmt(stmt, scope);
}

void scope_variables(Stmts *tree) {
    scope_counter = 0;
    root_scope[0] = 0;
    scope_levels[0]["write"] = Data(DATA_SEGMENT, "write", CONSTRUCTIONV, "ero_write");
    scope_levels[0]["true"] = Data(DATA_SEGMENT, "true", BOOL, "1");
    scope_levels[0]["false"] = Data(DATA_SEGMENT, "false", BOOL, "0");

    scope_queue.push({tree, scope_counter});
    while (!scope_queue.empty()) {
        auto [stmts, scope] = scope_queue.front();
        scope_queue.pop();
        scope_stmts(stmts, scope);
    }
}
