#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <math.h>

struct Vector3D {
    long double x, y, z;

    Vector3D() {
        x = 0, y = 0, z = 0;
    }

    Vector3D(long double x, long double y, long double z) : x(x), y(y), z(z) {}

    Vector3D operator + (const Vector3D& v) const {
        return Vector3D(x + v.x, y + v.y, z + v.z);
    }

    Vector3D operator - (const Vector3D& v) const {
        return Vector3D(x - v.x, y - v.y, z - v.z);
    }

    Vector3D operator * (const long double scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    Vector3D operator / (const long double scalar) const {
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

    long double mag() {
        return sqrt(x * x + y * y + z * z);
    }

    long double mag2() {
        return x * x + y * y + z * z;
    }

    long double dot(Vector3D& v) {
        return x * v.x + y * v.y + z * v.z;
    }

    Vector3D cross(Vector3D& v) {
        return Vector3D((y * v.z - z * v.y), (z * v.x - x * v.z), (x * v.y - y * v.x));
    }
};

#endif