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
    DisjunctionExpr &left;
    Token op;
    AssignmentExpr &right;
    AssignmentExpr(DisjunctionExpr left, Token op, AssignmentExpr right) : left(left), op(op), right(right) {}
};

struct DisjunctionExpr : Expr {
    DisjunctionExpr &left;
    Token op;
    XdisjunctionExpr &rightj;
    DisjunctionExpr(DisjunctionExpr left, Token op, XdisjunctionExpr right) : left(left), op(op), right(right) {}
};

struct XdisjunctionExpr : Expr {
    XdisjunctionExpr &left;
    Token op;
    ConjunctionExpr &right;
    XdisjunctionExpr(XdisjunctionExpr left, Token op, ConjunctionExpr right) : left(left), op(op), right(right) {}
};

struct ConjunctionExpr {
    ConjunctionExpr &left;
    Token op;
    ComparisonExpr &right;
    ConjunctionExpr(ConjunctionExpr left, Token op, ComparisonExpr right) : left(left), op(op), right(right) {}
};

struct ComparisonExpr {
    ComparisonExpr &left;
    Token op;
    AdditionExpr &right;
    ComparisonExpr(ComparisonExpr left, Token op, AdditionExpr right) : left(left), op(op), right(right) {}
};

struct AdditionExpr {
    AdditionExpr &left;
    Token op;
    MultiplicationExpr &right;
    AdditionExpr(AdditionExpr left, Token op, MultiplicationExpr right) : left(left), op(op), right(right) {}
};

struct MultiplicationExpr {
    MultiplicationExpr &left;
    Token op;
    ExponentiationExpr &right;
    MultiplicationExpr(MultiplicationExpr left, Token op, ExponentiationExpr right) : left(left), op(op), right(right) {}
};

struct ExponentiationExpr {
    
}

Stmts parse(vector<Token> &tokens);

#endif