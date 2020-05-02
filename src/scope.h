#ifndef SCOPE_H
#define SCOPE_H
#include <iostream>
#include <map>
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
    string pos;
    Var *value;

    Data() {}
    Data(DataLocation loc, string pos) : loc(loc), pos(pos), value(nullptr) {}
    Data(DataLocation loc, string pos, Var *value) : loc(loc), pos(pos), value(value) {}
};

map<int, map<string, Data>> scope_variables(Stmts *stmts);

#endif