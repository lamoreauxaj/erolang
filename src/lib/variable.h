#ifndef VARIABLE_H
#define VARIABLE_H

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
    CONSTRUCTION,
    TUPLE
};

struct Var {
    VarType type;
    int size;
};

struct RealVar : Var {
    double val;
    RealVar(double val) : val(val) {
        type = REALV;
        size = sizeof(RealVar);
    }
};

#endif