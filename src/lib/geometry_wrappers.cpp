#include "geometry_wrappers.h"

extern "C" Var ero_plane(Var *alpha, Var *beta, Var *gamma) {
    ero_error("plane is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var ero_sphere(Var *center, Var *point) {
    ero_error("sphere is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var ero_line(Var *alpha, Var *beta) {
    ero_error("line is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var ero_point(Var *x, Var *y, Var *z) {
    type_check(x, REALV);
    type_check(y, REALV);
    type_check(z, REALV);
    Vector3D p(as_double(x->val), as_double(y->val), as_double(z->val)); 
    Point *point = new Point(p);
    return Var(POINT, (uint64_t) point);
}

extern "C" Var ero_intersection(Var *alpha, Var *beta) {
    ero_error("intersection is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var ero_point_on(Var *alpha) {
    ero_error("point_on is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var ero_center(Var *alpha) {
    ero_error("center is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var ero_endpoints(Var *alpha) {
    ero_error("endpoints is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var ero_segment(Var *alpha, Var *beta) {
    ero_error("segment is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var ero_ray(Var *endpoint, Var *point) {
    ero_error("ray is unimplemented");
    return Var(UNDEFINED, 0);
}

extern "C" Var ero_arc(Var *start, Var *point, Var *end) {
    ero_error("arc is unimplemented");
    return Var(UNDEFINED, 0);
}

void ero_write_geometry(Var *figure) {
    if (figure->type == POINT) {
        Point *point = (Point*) figure->val;
        string json = "{\"figure\":\"point\",\"point\":[" + to_string(point->p.x) + "," + to_string(point->p.y) + "," + to_string(point->p.z) + "]}";
        cout << json << endl;
    }
    else {
        ero_error("write: unimplemented figure type");
    }
}
