#ifndef VARIABLE_H
#define VARIABLE_H

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

struct Vector3D {
    double x, y, z;

    Vector3D() {
        x = 0, y = 0, z = 0;
    }

    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

    Vector3D operator + (const Vector3D& v) const {
        return Vector3D(x + v.x, y + v.y, z + v.z);
    }

    Vector3D operator - (const Vector3D& v) const {
        return Vector3D(x - v.x, y - v.y, z - v.z);
    }

    Vector3D operator * (const double scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    Vector3D operator / (const double scalar) const {
        return Vector3D(x / scalar, y / scalar, z / scalar);
    }

    bool operator == (const Vector3D& v) const {
        return (x == v.x) && (y == v.y) && (z == v.z);
    }

    bool operator != (const Vector3D& v) const {
        return (x != v.x) || (y != v.y) || (z == v.z);
    }

    void operator = (const Vector3D& v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    double mag2() {
        return x * x + y * y + z * z;
    }

    Vector3D dot(Vector3D& v) {
        return Vector3D(x * v.x, y * v.y, z * v.z);
    }
};

struct Var {
    VarType type;
    int size;
};

struct RealVar : Var {
    double val;
    RealVar(double val) : val(val) {
        type = REALV;
        size = sizeof(RealVar);
    }
};

struct Point : Var {
    Vector3D v;
    Point(Vector3D v) : v(v) {
        type = POINT;
        size = sizeof(Point);
    }
};

struct Line : Var {
    Vector3D p, m;
    Line(Vector3D p, Vector3D m) : p(p), m(m) {
        type = LINE;
        size = sizeof(Line);
<<<<<<< HEAD
    }   
=======
    }
>>>>>>> 285f875a27974a5c270a9eee810b4869dab7cc33
};

#endif