#ifndef GEOMETRY_WRAPPERS_H
#define GEOMETRY_WRAPPERS_H
#include <iostream>
#include "error.h"
#include "geometry.h"
#include "util.h"
#include "variable.h"
using namespace std;

class Var;

extern "C" Var ero_plane(Var *alpha, Var *beta, Var *gamma);

extern "C" Var ero_sphere(Var *alpha, Var *beta);

extern "C" Var ero_line(Var *alpha, Var *beta);

extern "C" Var ero_point(Var *x, Var *y, Var *z);

extern "C" Var ero_intersection(Var *alpha, Var *beta);

extern "C" Var ero_point_on(Var *alpha);

extern "C" Var ero_center(Var *alpha);

extern "C" Var ero_endpoints(Var *alpha);

extern "C" Var ero_segment(Var *alpha, Var *beta);

extern "C" Var ero_ray(Var *endpoint, Var *point);

extern "C" Var ero_arc(Var *start, Var *point, Var *end);

void ero_write_geometry(Var *figure);

#endif