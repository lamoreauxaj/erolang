#ifndef SCOPE_H
#define SCOPE_H
#include <map>
#include <string>
#include "parser.h"
using namespace std;

enum DataLocation {
    DATA_SEGMENT, // store global and captured variables
    STACK // all other local variables
};

struct Data {
    DataLocation loc;
    int pos;
};

map<int, map<string, Data>> scope_variables(Stmts *stmts);

#endif