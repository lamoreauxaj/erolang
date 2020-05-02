#include "scope.h"

static map<int, map<string, Data>> scope_levels;

static void scope_whilestmt(WhileStmt *stmt) {

}

static void scope_ifstmt(IfStmt *stmt) {

}

static void scope_exprstmt(ExprStmt *stmt) {

}

static void scope_stmt(Stmt *stmt) {

}

static void scope_stmts(Stmts *stmts) {

}

map<int, map<string, Data>> scope_variables(Stmts *tree) {
    scope_stmts(tree);
    return scope_levels;
}
