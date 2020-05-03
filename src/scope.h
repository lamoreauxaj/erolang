#ifndef SCOPE_H
#define SCOPE_H
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include "parser.h"
#include "lib/variable.h"
using namespace std;

enum DataLocation {
    DATA_SEGMENT, // store global and captured variables
    STACK // all other local variables
};

struct Data {
    DataLocation loc;
    int pos;
    string label;
    Var *value;

    Data() {}
    // used for stack variables
    Data(DataLocation loc, int pos) : loc(loc), pos(pos), label(), value(nullptr) {}
    // used for data segment variables
    Data(DataLocation loc, string label) : loc(loc), pos(0), label(label), value(nullptr) {}
    // used for data segment variables with default value
    Data(DataLocation loc, string label, Var *value) : loc(loc), pos(0), label(label), value(value) {}
    string tostring() {
        string res = "(Data ";
        if (loc == 0) res += "DATA_SEGMENT";
        else res += "STACK";
        res += " " + to_string(pos) + " " + label + ")";
        return res;
    }
};

extern map<int, map<string, Data>> scope_levels;
extern map<int, int> parent_scope;
extern map<Node*, int> node_scopes;

void scope_variables(Stmts *stmts);

#endif