#include "scope.h"

map<Node*, int> node_scopes;
map<int, map<string, int>> scope_levels;
map<int, Data> data_locs;
map<int, int> parent_scope;
map<int, int> root_scope;
map<int, int> stack_size;

static int scope_counter;
static int data_counter;
static queue<pair<Stmts*, int>> scope_queue;

static void scope_stmts(Stmts *stmts, int scope);
static void scope_expr(Expr *expr, int scope);

static void resolve_identifier(string id, int scope) {
    int curr = scope;
    while (true) {
        if (scope_levels[curr].count(id)) {
            scope_levels[scope][id] = scope_levels[curr][id];
            // variable was captured (local scope outside function but not global scope)
            if (root_scope[scope] != root_scope[curr] && curr != 0) {
                // cout << "variable captured\n";
                int data_cnt = scope_levels[curr][id];
                if (data_locs[data_cnt].loc == STACK) {
                    stack_size[root_scope[curr]] -= VAR_SIZE;
                    data_locs[data_cnt] = Data(DATA_SEGMENT, id);
                }
            }
            break;
        }
        if (!parent_scope.count(curr)) {
            return;
        } 
        curr = parent_scope[curr];
    }
}

static void create_variable(string id, int scope) {
    cout << "creating: " << id << " in " << scope << " with root " << root_scope[scope] << " stack_size " << stack_size[root_scope[scope]] << "\n";
    if (scope == 0) {
        scope_levels[scope][id] = data_counter;
        data_locs[data_counter++] = Data(DATA_SEGMENT, id);
    }
    else {
        scope_levels[scope][id] = data_counter;
        data_locs[data_counter++] = Data(STACK, stack_size[root_scope[scope]]);
        stack_size[root_scope[scope]] += VAR_SIZE;
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
            create_variable(id, scope);
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
    if (!scope_levels[scope].count(id)) {
        log_error("unable to resolve variable");
        return;
    }
    /*
    string id = expr->val.text;
    if (!scope_levels[0].count(id)) {
        scope_levels[0][id] = Data(DATA_SEGMENT, id);
    }
    */
}

static void scope_construction_expr(ConstructionExpr *expr, int scope) {
    int next_scope = ++scope_counter;
    parent_scope[next_scope] = scope;
    root_scope[next_scope] = next_scope; // new root scope
    cout << "resetting stack size: " << next_scope << "\n";
    stack_size[next_scope] = 0;
    // inject parameters and return values into scope
    for (Expr *arg : expr->args->vals) {
        if (arg->type != IDENTIFIEREXPR) {
            log_error("expected identifier as arg");
            return;
        }
        IdentifierExpr *id = (IdentifierExpr*) arg;
        string name = id->val.text;
        create_variable(name, next_scope);
    }
    for (Expr *ret : expr->rets->vals) {
        if (ret->type != IDENTIFIEREXPR) {
            log_error("expected identifier as return");
            return;
        }
        IdentifierExpr *id = (IdentifierExpr*) ret;
        string name = id->val.text;
        create_variable(name, next_scope);

    }
    scope_stmts(expr->block, next_scope);
}

static void scope_expr(Expr *expr, int scope) {
    node_scopes[expr] = scope;
    if (expr->type == BINARYEXPR) scope_binary_expr((BinaryExpr*) expr, scope);
    else if (expr->type == UNARYEXPR) scope_unary_expr((UnaryExpr*) expr, scope);
    else if (expr->type == REALEXPR) scope_real_expr((RealExpr*) expr, scope);
    else if (expr->type == IDENTIFIEREXPR) scope_identifier_expr((IdentifierExpr*) expr, scope);
    else if (expr->type == CALLEXPR) scope_call_expr((CallExpr*) expr, scope);
    else if (expr->type == CONSTRUCTIONEXPR) scope_construction_expr((ConstructionExpr*) expr, scope);
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
    for (Stmt *stmt : stmts->stmts)
        scope_stmt(stmt, scope);
}

void scope_variables(Stmts *tree) {
    scope_counter = 0;
    data_counter = 0;
    root_scope[0] = 0;
    stack_size[0] = 0;
    scope_levels[0]["write"] = data_counter;
    data_locs[data_counter++] = Data(DATA_SEGMENT, "write", CONSTRUCTIONV, "ero_write");
    scope_levels[0]["true"] = data_counter;
    data_locs[data_counter++] = Data(DATA_SEGMENT, "true", BOOL, "1");
    scope_levels[0]["false"] = data_counter;
    data_locs[data_counter++] = Data(DATA_SEGMENT, "false", BOOL, "0");

    scope_queue.push({tree, scope_counter});
    while (!scope_queue.empty()) {
        auto [stmts, scope] = scope_queue.front();
        scope_queue.pop();
        scope_stmts(stmts, scope);
    }
}
