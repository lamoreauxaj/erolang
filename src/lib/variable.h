#ifndef VARIABLE_H
#define VARIABLE_H

#include "Vector3D.h"

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
    TUPLE,
    UNDEFINED
};

#endif