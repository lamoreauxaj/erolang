#include "geometry_wrappers.h"

extern "C" Var ero_plane(Var *alpha, Var *beta, Var *gamma) {
    type_check(alpha, POINT);
    type_check(beta, POINT);
    type_check(gamma, POINT);
    Vector3D x = ((Point*) alpha->val)->p - ((Point*) beta->val)->p;
    Vector3D y = ((Point*) gamma->val)->p - ((Point*) beta->val)->p;
    Vector3D norm = x.cross(y);
    if (isZeroVector(norm))
        return Var(UNDEFINED, 0);
    else {
        Plane *plane = new Plane(((Point*) beta->val)->p, norm);
        return Var(PLANE, (uint64_t) plane);
    }
}

extern "C" Var ero_sphere(Var *alpha, Var *beta) {
    type_check(alpha, POINT);
    type_check(beta, POINT);
    Vector3D center = ((Point*) alpha->val)->p;
    Vector3D point = ((Point*) beta->val)->p;
    if (isZeroVector(point - center))
        return Var(UNDEFINED, 0);
    else {
        Sphere *sphere = new Sphere(center, (point - center).mag());
        return Var(SPHERE, (uint64_t) sphere);
    }
}

extern "C" Var ero_line(Var *alpha, Var *beta) {
    type_check(alpha, POINT);
    type_check(beta, POINT);
    Vector3D point = ((Point*) alpha->val)->p;
    Vector3D slope = ((Point*) beta->val)->p - point;
    if (isZeroVector(slope))
        return Var(UNDEFINED, 0);
    else {
        Line *line = new Line(point, slope);
        return Var(LINE, (uint64_t) line);
    }
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
    else if (figure->type == LINE) {
        Line *line = (Line*) figure->val;
        string json = "{\"figure\":\"line\",\"point\":[" + to_string(line->p.x) + "," + to_string(line->p.y) + "," + to_string(line->p.z) + "],\"slope\":[" + to_string(line->m.x) + "," + to_string(line->m.y) + "," + to_string(line->m.z) + "]}";
        cout << json << endl;
    }
    else if (figure->type == SPHERE) {
        Sphere *sphere = (Sphere*) figure->val;
        string json = "{\"figure\":\"sphere\",\"center\":[" + to_string(sphere->p.x) + "," + to_string(sphere->p.y) + "," + to_string(sphere->p.z) + "],\"radius\":" + to_string(sphere->r) + "}";
        cout << json << endl;
    }
    else if (figure->type == PLANE) {
        Plane *plane = (Plane*) figure->val;
        string json = "{\"figure\":\"plane\",\"point\":[" + to_string(plane->p.x) + "," + to_string(plane->p.y) + "," + to_string(plane->p.z) + "],\"norm\":[" + to_string(plane->norm.x) + "," + to_string(plane->norm.y) + "," + to_string(plane->norm.z) + "]}";
        cout << json << endl;
    }
    else {
        ero_error("write: unimplemented figure type");
    }
}
