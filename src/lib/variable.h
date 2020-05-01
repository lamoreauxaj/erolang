#ifndef VARIABLE_H
#define VARIABLE_H

enum VarType {
    REALV,
    POINT,
    LINE,
    SEGMENT,
    RAY,
    PLANE,
    CIRCLE,
    ARC,
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