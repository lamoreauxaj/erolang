#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include "lexer.h"
#include "log.h"
using namespace std;

struct Node {
};

struct Stmt : Node {
};

struct Expr : Node {
};

struct Stmts : Node {
    vector<Stmt> stmts;
    Stmts() {}
    Stmts(vector<Stmt> stmts) stmts(stmts) {}
};

struct IfStmt : Stmt {
    Expr cond;
    Stmts block;
    IfStmt() {}
    IfStmt(Expr cond, Stmts block) : cond(cond), block(block) {}
};

struct WhileStmt : Stmt {
    Expr cond;
    Stmts block;
    WhileStmt() {}
    WhileStmt(Expr cond, Stmts block) : cond(cond), block(block) {}
};

struct ExprStmt : Stmt {
    AssignmentExpr expr;
    ExprStmt() {}
    ExprStat(AssignmentExpr expr) : expr(expr) {}
};

struct AssignmentExpr : Expr {
    DisjunctionExpr &left;
    Token op;
    AssignmentExpr &right;
    AssignmentExpr() {}
    AssignmentExpr(DisjunctionExpr left, Token op, AssignmentExpr right) : left(left), op(op), right(right) {}
};

struct DisjunctionExpr : Expr {
    DisjunctionExpr &left;
    Token op;
    XdisjunctionExpr &rightj;
    DisjunctionExpr() {}
    DisjunctionExpr(DisjunctionExpr left, Token op, XdisjunctionExpr right) : left(left), op(op), right(right) {}
};

struct XdisjunctionExpr : Expr {
    XdisjunctionExpr &left;
    Token op;
    ConjunctionExpr &right;
    XdisjunctionExpr() {}
    XdisjunctionExpr(XdisjunctionExpr left, Token op, ConjunctionExpr right) : left(left), op(op), right(right) {}
};

struct ConjunctionExpr : Expr {
    ConjunctionExpr &left;
    Token op;
    ComparisonExpr &right;
    ConjunctionExpr() {}
    ConjunctionExpr(ConjunctionExpr left, Token op, ComparisonExpr right) : left(left), op(op), right(right) {}
};

struct ComparisonExpr : Expr {
    ComparisonExpr &left;
    Token op;
    AdditionExpr &right;
    ComparisonExpr() {}
    ComparisonExpr(ComparisonExpr left, Token op, AdditionExpr right) : left(left), op(op), right(right) {}
};

struct AdditionExpr : Expr {
    AdditionExpr &left;
    Token op;
    MultiplicationExpr &right;
    AdditionExpr() {}
    AdditionExpr(AdditionExpr left, Token op, MultiplicationExpr right) : left(left), op(op), right(right) {}
};

struct MultiplicationExpr : Expr {
    MultiplicationExpr &left;
    Token op;
    ExponentiationExpr &right;
    MultiplicationExpr() {}
    MultiplicationExpr(MultiplicationExpr left, Token op, ExponentiationExpr right) : left(left), op(op), right(right) {}
};

struct ExponentiationExpr : Expr {
    UnaryExpr &left;
    Token op;
    ExponentiationExpr &right;
    ExponentiationExpr() {}
    ExponentiationExpr(UnaryExpr left, Token op, ExponentiationExpr right) : left(left), op(op), right(right) {}
}

struct UnaryExpr : Expr {
    Token op;
    PrimaryExpr val;
    UnaryExpr() {}
    UnaryExpr(Token op, PrimaryExpr val) : op(op), val(val) {}
};

struct PrimaryExpr : Expr {
};

struct RealExpr : PrimaryExpr {
    Token val;
    RealExpr() {}
    RealExpr(Token val) : val(val) {}
};

struct IdentifierExpr : PrimaryExpr {
    Token val;
    IdentifierExpr() {}
    IdentifierExpr(Token val) val(val) {}
};

struct GroupExpr : PrimaryExpr {
    Expr val;
    GroupExpr() {}
    GroupExpr(Expr val) : val(val) {}
};

struct TupleExpr : PrimaryExpr {
    vector<Expr> vals;
    TupleExpr() {}
    TupleExpr(vector<Expr> vals) vals(vals) {}
};

struct CallExpr : PrimaryExpr {
    Expr val;
    TupleExpr args;
    CallExpr() {}
    CallExpr(Expr val, TupleExpr args) val(val), args(args) {}
};

struct IndexExpr : PrimaryExpr {
    Expr val;
    Expr index;
    IndexExpr() {}
    IndexExpr(Expr val, Expr index) : val(val), index(index) {}
};

Stmts parse(vector<Token> &tokens);

#endif