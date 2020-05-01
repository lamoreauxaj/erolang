#include "compile.h"

enum DataLocation {
    DATA_SEGMENT, // store global and captured variables
    STACK // all other local variables
};

struct Data {
    DataLocation loc;
    int pos;
};

map<int, map<string, Data>> scope_levels;
queue<Node*> function_queue;

void compile_stmt(Stmt *stmt) {

}

void compile_stmts(Stmts *node) {
    for (Stmt *child : node->stmts) {

    }
}

void compile(Node *tree) {

}
