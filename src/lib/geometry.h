#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <utility>
#include <vector>
#include "Vector3D.h"
#include "variable.h"

using namespace std;

bool withinEps(long double a, long double b) {
    return abs(a - b) <= 1e-6;
}

struct Figure {};

struct Sphere;
struct Circle;
struct Plane;

struct Point : Figure {
    Vector3D p;
    Point(Vector3D p) : p(p) {}
};

struct Line : Figure {
    Vector3D p;
    Vector3D m;

    Line(Vector3D p, Vector3D m) : p(p), m(m) {}

    vector<pair<VarType, Figure>> intersect(Point p);
    vector<pair<VarType, Figure>> intersect(Line l);
    vector<pair<VarType, Figure>> intersect(Circle c);
    vector<pair<VarType, Figure>> intersect(Plane p);
    vector<pair<VarType, Figure>> intersect(Sphere s);
    vector<pair<VarType, Figure>> pointOn();
};

struct Plane : Figure {
    Vector3D p;
    Vector3D norm;

    Plane(Vector3D p, Vector3D norm) : p(p), norm(norm) {}
};

struct Circle : Figure {
    Vector3D p;
    double r;

    Circle(Vector3D p, double r) : p(p), r(r) {}
};

struct Sphere : Figure {
    Vector3D p;
    double r;
    
    Sphere(Vector3D p, double r) : p(p), r(r) {}
};

struct Empty : Figure {
    Empty() {}
};

struct Space : Figure {
    Space() {}
};

struct Construction : Figure {
    Construction() {}
};

struct Undefined : Figure {
    Undefined() {}
};

#endif
