#ifndef GEOMETRY_WRAPPERS_H
#define GEOMETRY_WRAPPERS_H
#include <iostream>
#include "error.h"
#include "variable.h"
using namespace std;

extern "C" Var plane(Var *alpha, Var *beta, Var *gamma);

extern "C" Var sphere(Var *center, Var *point);

extern "C" Var line(Var *alpha, Var *beta);

extern "C" Var point(Var *x, Var *y, Var *z);

extern "C" Var intersection(Var *alpha, Var *beta);

extern "C" Var point_on(Var *alpha);

extern "C" Var center(Var *alpha);

extern "C" Var endpoints(Var *alpha);

extern "C" Var segment(Var *alpha, Var *beta);

extern "C" Var ray(Var *endpoint, Var *point);

extern "C" Var arc(Var *start, Var *point, Var *end);

#endif