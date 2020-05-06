#include "geometry_wrappers.h"

extern "C" Var plane(Var *alpha, Var *beta, Var *gamma) {
    ero_error("plane is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var sphere(Var *center, Var *point) {
    ero_error("sphere is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var line(Var *alpha, Var *beta) {
    ero_error("line is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var point(Var *x, Var *y, Var *z) {
    ero_error("point is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var intersection(Var *alpha, Var *beta) {
    ero_error("intersection is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var point_on(Var *alpha) {
    ero_error("point_on is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var center(Var *alpha) {
    ero_error("center is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var endpoints(Var *alpha) {
    ero_error("endpoints is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var segment(Var *alpha, Var *beta) {
    ero_error("segment is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var ray(Var *endpoint, Var *point) {
    ero_error("ray is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var arc(Var *start, Var *point, Var *end) {
    ero_error("arc is unimplemented");
    return Var(UNDEFINED, 0);
}
