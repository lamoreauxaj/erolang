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

bool isZeroVector(const Vector3D v) {
    return withinEps(v.x, 0) && withinEps(v.y, 0) && withinEps(v.z, 0);
}

struct Figure {};

struct Point;
struct Line;
struct Circle;
struct Plane;
struct Sphere;

struct Point : Figure {
    Vector3D p;

    Point(Vector3D p) : p(p) {}

    vector<pair<VarType, Figure>> intersect(Point p);
    vector<pair<VarType, Figure>> intersect(Line l);
    vector<pair<VarType, Figure>> intersect(Circle c);
    vector<pair<VarType, Figure>> intersect(Plane p);
    vector<pair<VarType, Figure>> intersect(Sphere s);
    vector<pair<VarType, Figure>> pointOn();

    bool operator == (const Point& point) const {
        return p == point.p;
    }
    
    bool operator != (const Point& point) const {
        return !(*this == point);
    }
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

    bool operator == (const Line& line) const {
        return isZeroVector(m.cross(line.m)) && isZeroVector(m.cross(p - line.p));
    }

    bool operator != (const Line& line) const {
        return !(*this == line);
    }
};

struct Circle : Figure {
    Vector3D p, norm;
    long double r;

    Circle(Vector3D p, Vector3D norm, long double r) : p(p), norm(norm), r(r) {}

    vector<pair<VarType, Figure>> intersect(Point p);
    vector<pair<VarType, Figure>> intersect(Line l);
    vector<pair<VarType, Figure>> intersect(Circle c);
    vector<pair<VarType, Figure>> intersect(Plane p);
    vector<pair<VarType, Figure>> intersect(Sphere s);
    vector<pair<VarType, Figure>> pointOn();

    bool operator == (const Circle& circle) const {
        return isZeroVector(p - circle.p) && withinEps(r, circle.r) && isZeroVector(norm.cross(circle.norm));
    }

    bool operator != (const Circle& circle) const {
        return !(*this == circle);
    }
};

struct Plane : Figure {
    Vector3D p, norm;

    Plane(Vector3D p, Vector3D norm) : p(p), norm(norm) {}

    vector<pair<VarType, Figure>> intersect(Point p);
    vector<pair<VarType, Figure>> intersect(Line l);
    vector<pair<VarType, Figure>> intersect(Circle c);
    vector<pair<VarType, Figure>> intersect(Plane p);
    vector<pair<VarType, Figure>> intersect(Sphere s);
    vector<pair<VarType, Figure>> pointOn();

    bool operator == (const Plane& plane) const {
        return isZeroVector(norm.cross(plane.norm)) && withinEps(norm.dot(p - plane.p), 0);
    }

    bool operator != (const Plane& plane) const {
        return !(*this == plane);
    }
};

struct Sphere : Figure {
    Vector3D p;
    long double r;
    
    Sphere(Vector3D p, long double r) : p(p), r(r) {}

    vector<pair<VarType, Figure>> intersect(Point p);
    vector<pair<VarType, Figure>> intersect(Line l);
    vector<pair<VarType, Figure>> intersect(Circle c);
    vector<pair<VarType, Figure>> intersect(Plane p);
    vector<pair<VarType, Figure>> intersect(Sphere s);
    vector<pair<VarType, Figure>> pointOn();

    bool operator == (const Sphere& sphere) const {
        return isZeroVector(p - sphere.p) && withinEps(r, sphere.r);
    }

    bool operator != (const Sphere& sphere) const {
        return !(*this == sphere);
    }
};

struct Empty : Figure {
    Empty() {}

    vector<pair<VarType, Figure>> intersect(Point p);
    vector<pair<VarType, Figure>> intersect(Line l);
    vector<pair<VarType, Figure>> intersect(Circle c);
    vector<pair<VarType, Figure>> intersect(Plane p);
    vector<pair<VarType, Figure>> intersect(Sphere s);
    vector<pair<VarType, Figure>> pointOn();
};

struct Space : Figure {
    Space() {}

    vector<pair<VarType, Figure>> intersect(Point p);
    vector<pair<VarType, Figure>> intersect(Line l);
    vector<pair<VarType, Figure>> intersect(Circle c);
    vector<pair<VarType, Figure>> intersect(Plane p);
    vector<pair<VarType, Figure>> intersect(Sphere s);
    vector<pair<VarType, Figure>> pointOn();
};

struct Construction : Figure {
    Construction() {}

    vector<pair<VarType, Figure>> intersect(Point p);
    vector<pair<VarType, Figure>> intersect(Line l);
    vector<pair<VarType, Figure>> intersect(Circle c);
    vector<pair<VarType, Figure>> intersect(Plane p);
    vector<pair<VarType, Figure>> intersect(Sphere s);
    vector<pair<VarType, Figure>> pointOn();
};

struct Undefined : Figure {
    Undefined() {}

    vector<pair<VarType, Figure>> intersect(Point p);
    vector<pair<VarType, Figure>> intersect(Line l);
    vector<pair<VarType, Figure>> intersect(Circle c);
    vector<pair<VarType, Figure>> intersect(Plane p);
    vector<pair<VarType, Figure>> intersect(Sphere s);
    vector<pair<VarType, Figure>> pointOn();
};

#endif
