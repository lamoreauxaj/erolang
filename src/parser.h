#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <optional>
#include <vector>
#include "lexer.h"
#include "log.h"
using namespace std;

enum NodeType {
    NODE, STMT, EXPR, STMTS, IFSTMT, WHILESTMT, EXPRSTMT, REALEXPR, IDENTIFIEREXPR,
    GROUPEXPR, TUPLEEXPR, CALLEXPR, INDEXEXPR, UNARYEXPR, BINARYEXPR
};

struct Node {
    NodeType type = NODE;
    virtual string pprint() = 0;
};

inline string pprinter(Node *node) {
    if (node == nullptr) return "NULL";
    return node->pprint();
}

struct Stmt : virtual Node {
    Stmt() { type = STMT; }
    string pprint() { return "TODO"; }
};

struct Expr : virtual Node {
    Expr() { type = EXPR; }
    string pprint() { return "TODO"; }
};

struct Stmts : virtual Node {
    vector<Stmt*> stmts;
    Stmts() { type = STMTS; }
    Stmts(vector<Stmt*> stmts) : stmts(stmts) { type = STMTS; }
    ~Stmts() { for (auto i : stmts) delete i; }
    string pprint() {
        string res = "(Stmts ";
        for (Stmt *stmt : stmts)
            res += pprinter(stmt);
        res += ")";
        return res;
    }
};

struct IfStmt : Stmt {
    Expr *cond;
    Stmts *block;
    IfStmt() { type = IFSTMT; }
    IfStmt(Expr *cond, Stmts *block) : cond(cond), block(block) { type = IFSTMT; }
    ~IfStmt() { delete cond; delete block; }
    string pprint() { return "TODO"; }
};

struct WhileStmt : Stmt {
    Expr *cond;
    Stmts *block;
    WhileStmt() { type = WHILESTMT; }
    WhileStmt(Expr *cond, Stmts *block) : cond(cond), block(block) { type = WHILESTMT; }
    ~WhileStmt() { delete cond; delete block; }
    string pprint() { return "TODO"; }
};

struct RealExpr : Expr {
    Token val;
    RealExpr() { type = REALEXPR; }
    RealExpr(Token val) : val(val) { type = REALEXPR; }
    string pprint() { return "(RealExpr " + val.text + ")"; }
};

struct IdentifierExpr : Expr {
    Token val;
    IdentifierExpr() { type = IDENTIFIEREXPR; }
    IdentifierExpr(Token val) : val(val) { type = IDENTIFIEREXPR; }
    string pprint() { return "(IdentifierExpr " + val.text + ")"; }
};

struct GroupExpr : Expr {
    Expr *val;
    GroupExpr() { type = GROUPEXPR; }
    GroupExpr(Expr *val) : val(val) { type = GROUPEXPR; }
    ~GroupExpr() { delete val; }
    string pprint() { return "(GroupExpr " + pprinter(val) + ")"; }
};

struct TupleExpr : Expr {
    vector<Expr*> vals;
    TupleExpr() { type = TUPLEEXPR; }
    TupleExpr(vector<Expr*> vals) : vals(vals) { type = TUPLEEXPR; }
    ~TupleExpr() { for (auto i : vals) delete i; }
    string pprint() { return "TODO"; }
};

struct CallExpr : Expr {
    Expr *val;
    TupleExpr *args;
    CallExpr() { type = CALLEXPR; }
    CallExpr(Expr *val, TupleExpr *args) : val(val), args(args) { type = CALLEXPR; }
    ~CallExpr() { delete val; delete args; }
    string pprint() { return "TODO"; }
};

struct IndexExpr : Expr {
    Expr *val;
    Expr *index;
    IndexExpr() { type = INDEXEXPR; }
    IndexExpr(Expr *val, Expr *index) : val(val), index(index) { type = INDEXEXPR; }
    ~IndexExpr() { delete val; delete index; }
    string pprint() { return "TODO"; }
};

struct UnaryExpr : Expr {
    Token op;
    Expr *val;
    UnaryExpr() { type = UNARYEXPR; }
    UnaryExpr(Token op, Expr *val) : op(op), val(val) { type = UNARYEXPR; }
    ~UnaryExpr() { delete val; }
    string pprint() { return "TODO"; }
};

struct BinaryExpr : Expr {
    Expr *left;
    Token op;
    Token xop;
    Expr *right;
    BinaryExpr() { type = BINARYEXPR; }
    BinaryExpr(Expr *left, Token op, Expr *right) : left(left), op(op), right(right) { type = BINARYEXPR; }
    BinaryExpr(Expr *left, Token op, Token xop, Expr *right) : left(left), op(op), xop(xop), right(right) { type = BINARYEXPR; }
    string pprint() { return "(BinaryExpr " + left->pprint() + " " + op.text + " " + right->pprint() + ")"; }
};

struct ExprStmt : Stmt {
    Expr *expr;
    ExprStmt() { type = EXPRSTMT; }
    ExprStmt(Expr *expr) : expr(expr) { type = EXPRSTMT; }
    ~ExprStmt() { delete expr; }
    string pprint() { return "(ExprStmt " + expr->pprint() + ")"; }
};

Stmts *parse(vector<Token> &tokens);

#endif