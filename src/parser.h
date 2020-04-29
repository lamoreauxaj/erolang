#ifndef PARSER_H
#define PARSER_H
#include <optional>
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
    vector<Stmt*> stmts;
    Stmts() {}
    Stmts(vector<Stmt*> stmts) : stmts(stmts) {}
    ~Stmts() { for (auto i : stmts) delete i; }
};

struct IfStmt : Stmt {
    Expr *cond;
    Stmts *block;
    IfStmt() {}
    IfStmt(Expr *cond, Stmts *block) : cond(cond), block(block) {}
    ~IfStmt() { delete cond; delete block; }
};

struct WhileStmt : Stmt {
    Expr *cond;
    Stmts *block;
    WhileStmt() {}
    WhileStmt(Expr *cond, Stmts *block) : cond(cond), block(block) {}
    ~WhileStmt() { delete cond; delete block; }
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
    IdentifierExpr(Token val) : val(val) {}
};

struct GroupExpr : PrimaryExpr {
    Expr *val;
    GroupExpr() {}
    GroupExpr(Expr *val) : val(val) {}
    ~GroupExpr() { delete val; }
};

struct TupleExpr : PrimaryExpr {
    vector<Expr*> vals;
    TupleExpr() {}
    TupleExpr(vector<Expr*> vals) : vals(vals) {}
    ~TupleExpr() { for (auto i : vals) delete i; }
};

struct CallExpr : PrimaryExpr {
    Expr *val;
    TupleExpr *args;
    CallExpr() {}
    CallExpr(Expr *val, TupleExpr *args) : val(val), args(args) {}
    ~CallExpr() { delete val; delete args; }
};

struct IndexExpr : PrimaryExpr {
    Expr *val;
    Expr *index;
    IndexExpr() {}
    IndexExpr(Expr *val, Expr *index) : val(val), index(index) {}
    ~IndexExpr() { delete val; delete index; }
};

struct UnaryExpr : Expr {
    Token op;
    PrimaryExpr *val;
    UnaryExpr() {}
    UnaryExpr(Token op, PrimaryExpr *val) : op(op), val(val) {}
    ~UnaryExpr() { delete val; }
};

struct ExponentiationExpr : Expr {
    UnaryExpr *left;
    Token op;
    ExponentiationExpr *right;
    ExponentiationExpr() {}
    ExponentiationExpr(UnaryExpr *left) : left(left) {}
    ExponentiationExpr(UnaryExpr *left, Token op, ExponentiationExpr *right) : left(left), op(op), right(right) {}
    ~ExponentiationExpr() { delete left; delete right; }
};

struct MultiplicationExpr : Expr {
    MultiplicationExpr *left;
    Token op;
    ExponentiationExpr *right;
    MultiplicationExpr() {}
    MultiplicationExpr(ExponentiationExpr *right) : right(right) {}
    MultiplicationExpr(MultiplicationExpr *left, Token op, ExponentiationExpr *right) : left(left), op(op), right(right) {}
    ~MultiplicationExpr() { delete left; delete right; }
};

struct AdditionExpr : Expr {
    AdditionExpr *left;
    Token op;
    MultiplicationExpr *right;
    AdditionExpr() {}
    AdditionExpr(MultiplicationExpr *right) : right(right) {}
    AdditionExpr(AdditionExpr *left, Token op, MultiplicationExpr *right) : left(left), op(op), right(right) {}
    ~AdditionExpr() { delete left; delete right; }
};

struct ComparisonExpr : Expr {
    ComparisonExpr *left;
    Token op;
    AdditionExpr *right;
    ComparisonExpr() {}
    ComparisonExpr(AdditionExpr *right) : right(right) {}
    ComparisonExpr(ComparisonExpr *left, Token op, AdditionExpr *right) : left(left), op(op), right(right) {}
    ~ComparisonExpr() { delete left; delete right; }
};

struct ConjunctionExpr : Expr {
    ConjunctionExpr *left;
    Token op;
    ComparisonExpr *right;
    ConjunctionExpr() {}
    ConjunctionExpr(ComparisonExpr *right) : right(right) {}
    ConjunctionExpr(ConjunctionExpr *left, Token op, ComparisonExpr *right) : left(left), op(op), right(right) {}
    ~ConjunctionExpr() { delete left; delete right; }
};

struct XdisjunctionExpr : Expr {
    XdisjunctionExpr *left;
    Token op;
    ConjunctionExpr *right;
    XdisjunctionExpr() {}
    XdisjunctionExpr(ConjunctionExpr *right) : right(right) {}
    XdisjunctionExpr(XdisjunctionExpr *left, Token op, ConjunctionExpr *right) : left(left), op(op), right(right) {}
};

struct DisjunctionExpr : Expr {
    DisjunctionExpr *left;
    Token op;
    XdisjunctionExpr *right;
    DisjunctionExpr() {}
    DisjunctionExpr(XdisjunctionExpr *right) : right(right) {}
    DisjunctionExpr(DisjunctionExpr *left, Token op, XdisjunctionExpr *right) : left(left), op(op), right(right) {}
};

struct AssignmentExpr : Expr {
    DisjunctionExpr *left;
    Token op;
    AssignmentExpr *right;
    AssignmentExpr() {}
    AssignmentExpr(DisjunctionExpr *left) : left(left) {}
    AssignmentExpr(DisjunctionExpr *left, Token op, AssignmentExpr *right) : left(left), op(op), right(right) {}
    ~AssignmentExpr() { delete left; delete right; }
};

struct ExprStmt : Stmt {
    AssignmentExpr *expr;
    ExprStmt() {}
    ExprStmt(AssignmentExpr *expr) : expr(expr) {}
    ~ExprStmt() { delete expr; }
};

Stmts parse(vector<Token> &tokens);

#endif