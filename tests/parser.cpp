#include "gtest/gtest.h"
#include "parser.h"
using namespace std;

void check_tree(Node *tree, Node *exp) {

}

TEST(parser1, assigment1) {
    vector<Token> tok = {
        Token(IDENTIFIER, "a"),
        Token(ASSIGN, "="),
        Token(REAL, "1.0"),
        Token(NEWLINE, "\n")
    };
    Stmts *exp = new Stmts({
        new ExprStmt(
            new BinaryExpr(
                new IdentifierExpr(Token(IDENTIFIER, "a")),
                Token(ASSIGN, "="),
                new RealExpr(Token(REAL, "1.0"))
            )
        )
    });
    Stmts *tree = parse(tok);
    cout << pprinter(tree) << "\n";
    check_tree(tree, exp);
}