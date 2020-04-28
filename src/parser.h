#ifndef PARSER_H
#define PARSER_H

struct ASTNode {
};

struct StatementNode : ASTNode {
};

struct ExpressionNode : ASTNode {
};

struct StatementsNode : ASTNode {
    vector<Statement> children;
};

struct RealNode : ASTNode {
};

ASTNode parse(vector<Token> &tokens);

#endif