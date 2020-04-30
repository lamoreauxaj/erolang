#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <optional>
#include <vector>
#include "lexer.h"
#include "log.h"
using namespace std;

struct Node {
    virtual string pprint() = 0;
};

inline string pprinter(Node *node) {
    if (node == nullptr) return "NULL";
    return node->pprint();
}

struct Stmt : virtual Node {
};

struct Expr : virtual Node {
};

struct Stmts : virtual Node {
    vector<Stmt*> stmts;
    Stmts() {}
    Stmts(vector<Stmt*> stmts) : stmts(stmts) {}
    ~Stmts() { for (auto i : stmts) delete i; }
    string pprint() {
        string res = "(Stmts ";
        for (Stmt *stmt : stmts)
            res += pprinter(stmt);
        res += ")";
        return res;
    }
};

struct IfStmt : virtual Stmt {
    Expr *cond;
    Stmts *block;
    IfStmt() {}
    IfStmt(Expr *cond, Stmts *block) : cond(cond), block(block) {}
    ~IfStmt() { delete cond; delete block; }
    string pprint() { return "TODO"; }
};

struct WhileStmt : virtual Stmt {
    Expr *cond;
    Stmts *block;
    WhileStmt() {}
    WhileStmt(Expr *cond, Stmts *block) : cond(cond), block(block) {}
    ~WhileStmt() { delete cond; delete block; }
    string pprint() { return "TODO"; }
};

struct RealExpr : virtual Expr {
    Token val;
    RealExpr() {}
    RealExpr(Token val) : val(val) {}
    string pprint() { return "(RealExpr " + val.text + ")"; }
};

struct IdentifierExpr : virtual Expr {
    Token val;
    IdentifierExpr() {}
    IdentifierExpr(Token val) : val(val) {}
    string pprint() { return "(IdentifierExpr " + val.text + ")"; }
};

struct GroupExpr : virtual Expr {
    Expr *val;
    GroupExpr() {}
    GroupExpr(Expr *val) : val(val) {}
    ~GroupExpr() { delete val; }
    string pprint() { return "(GroupExpr " + pprinter(val) + ")"; }
};

struct TupleExpr : virtual Expr {
    vector<Expr*> vals;
    TupleExpr() {}
    TupleExpr(vector<Expr*> vals) : vals(vals) {}
    ~TupleExpr() { for (auto i : vals) delete i; }
    string pprint() { return "TODO"; }
};

struct CallExpr : virtual Expr {
    Expr *val;
    TupleExpr *args;
    CallExpr() {}
    CallExpr(Expr *val, TupleExpr *args) : val(val), args(args) {}
    ~CallExpr() { delete val; delete args; }
    string pprint() { return "TODO"; }
};

struct IndexExpr : virtual Expr {
    Expr *val;
    Expr *index;
    IndexExpr() {}
    IndexExpr(Expr *val, Expr *index) : val(val), index(index) {}
    ~IndexExpr() { delete val; delete index; }
    string pprint() { return "TODO"; }
};

struct UnaryExpr : virtual Expr {
    Token op;
    Expr *val;
    UnaryExpr() {}
    UnaryExpr(Token op, Expr *val) : op(op), val(val) {}
    ~UnaryExpr() { delete val; }
    string pprint() { return "TODO"; }
};

struct BinaryExpr : virtual Expr {
    Expr *left;
    Token op;
    Expr *right;
    BinaryExpr() {}
    BinaryExpr(Expr *left, Token op, Expr *right) : left(left), op(op), right(right) {}
    string pprint() { return "(BinaryExpr " + left->pprint() + " " + op.text + " " + right->pprint() + ")"; }
};

struct ExprStmt : virtual Stmt {
    Expr *expr;
    ExprStmt() {}
    ExprStmt(Expr *expr) : expr(expr) {}
    ~ExprStmt() { delete expr; }
    string pprint() { return "(ExprStmt " + expr->pprint() + ")"; }
};

Stmts *parse(vector<Token> &tokens);

#endif