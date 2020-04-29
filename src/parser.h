#ifndef PARSER_H
#define PARSER_H

struct Node {
};

struct Stmt : Node {
};

struct Expr : Node {
};

struct Statements : Node {
    vector<Statement> children;
};

struct GroupExpr : Node {
};

struct TupleExpr : Node {
};

struct RealExpr : Node {
    Token val;
    RealExpr(Token val) : val(val) {}
};

struct StringExpr : Node {
    Token val;
};

struct IdentifierExpr : Node {
    Token val;
};

struct PimaryExpr : Node {
};

struct UnaryExpr : Node {
};

struct ExponentiationExpr : Node {
};

struct MultiplicationExpr : Node {
};

struct AdditionExpr : Node {
};

struct ComparisonExpr : Node {
};

struct AssignmentExpr : Node {
};

ASTNode parse(vector<Token> &tokens);

#endif