#ifndef VARIABLE_H
#define VARIABLE_H
#include <cstdint>
#include <iostream>
#include "Vector3D.h"
using namespace std;

enum VarType {
    REALV,
    POINT,
    LINE,
    SEGMENT, // later
    RAY,     // later
    PLANE,
    CIRCLE,
    ARC,     // later
    SPHERE,
    EMPTY,
    SPACE,
    CONSTRUCTIONV,
    TUPLE,
    UNDEFINED
};

struct Var {
    VarType type;
    uint64_t val;

    Var(VarType type, uint64_t val) : type(type), val(val) {}
};

extern "C" Var ero_write(Var *var);

#endif