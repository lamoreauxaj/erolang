#ifndef VECTOR3D_H
#define VECTOR3D_H

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

#endif