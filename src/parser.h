#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include "lexer.h"
using namespace std;

struct Node {
};

struct Stmt : Node {
};

struct Expr : Node {
};

struct Stmts : Node {
    vector<Stmt> children;
};

struct IfStmt : Stmt {
    Expr cond;
    Stmts block;
};

struct WhileStmt : Stmt {
    Expr cond;
    Stmts block;
};

struct ExprStmt : Stmt {
    AssignmentExpr expr;
};

struct AssignmentExpr : Expr {
    AssignmentExpr &left;
    Token op;
    DisjunctionExpr &right;
    AssignmentExpr(AssignmentExpr left, Token op, DisjunctionExpr right) : left(left), op(op), right(right) {}
};

struct DisjunctionExpr : Expr {
    XdisjunctionExpr &left;
    Token op;
    DisjunctionExpr &right;
    DisjunctionExpr(XdisjunctionExpr left, Token op, DisjunctionExpr right) : left(left), op(op), right(right) {}
};

struct XdisjunctionExpr : Expr {
    ConjunctionExpr &left;
    Token op;
    XdisjunctionExpr &right;
    XdisjunctionExpr(ConjunctionExpr left, Token op, XdisjunctionExpr right) : left(left), op(op), right(right) {}
};

struct ConjunctionExpr {
    ComparisonExpr &left;
    Token op;
    ConjunctionExpr &right;
    ConjunctionExpr(ComparisonExpr left, Token op, ConjunctionExpr right) : left(left), op(op), right(right) {}
};

struct ComparisonExpr {
    AdditionExpr &left;
    Token op;
    ComparisonExpr &right;
    ComparisonExpr(AdditionExpr left, Token op, ComparisonExpr right) : left(left), op(op), right(right) {}
};

Stmts parse(vector<Token> &tokens);

#endif