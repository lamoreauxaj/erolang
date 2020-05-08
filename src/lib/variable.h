#ifndef VARIABLE_H
#define VARIABLE_H
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include "error.h"
#include "geometry_wrappers.h"
#include "util.h"
#include "Vector3D.h"
#include "vartype.h"
using namespace std;

const double EPS = 1e-6;

struct Var {
    VarType type;
    uint64_t val;

    Var(VarType type, uint64_t val) : type(type), val(val) {}
};

extern "C" Var ero_write(Var *var);

extern "C" Var ero_equals(Var *a, Var *b);

#endif