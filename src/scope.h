#ifndef SCOPE_H
#define SCOPE_H
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include "parser.h"
using namespace std;

enum DataLocation {
    DATA_SEGMENT, // store global and captured variables
    STACK // all other local variables
};

struct Data {
    DataLocation loc;
    string pos;

    Data() {}
    Data(DataLocation loc, string pos) : loc(loc), pos(pos) {}
};

map<int, map<string, Data>> scope_variables(Stmts *stmts);

#endif