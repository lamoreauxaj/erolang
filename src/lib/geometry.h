#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include "Vector3D.h"
#include "variable.h"

struct Figure {};

struct Point : Figure {
    Vector3D v;
    Point(Vector3D v) : v(v) {}
};

struct Line : Figure {
    Vector3D p;
    Vector3D m;
    Line(Vector3D p, Vector3D m) : p(p), m(m) {}

    vector<Figure> intersect(Point p) {
        vector<Figure> ret;

        return ret;
    }

    vector<Figure> intersect(Line l) {
        
    }
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
