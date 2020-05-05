#include "geometry.h"

// -------------------------------------------------------------------------------------------------------
// POINT
// -------------------------------------------------------------------------------------------------------

vector<pair<VarType, Figure*>> Point::intersect(Point point) {
    vector<pair<VarType, Figure*>> ret;

    if (p == point.p)
        ret.push_back(make_pair(POINT, this));
    
    return ret;
}

vector<pair<VarType, Figure*>> Point::intersect(Line line) {
    vector<pair<VarType, Figure*>> ret;

    Vector3D norm = (line.p - p).cross(line.m);
    if (isZeroVector(norm))
        ret.push_back(make_pair(POINT, this));

    return ret;
}

vector<pair<VarType, Figure*>> Point::intersect(Circle circle) {
    vector<pair<VarType, Figure*>> ret;

    if (withinEps(circle.norm.dot(circle.p - p), 0) && withinEps((p - circle.p).mag(), circle.r))
        ret.push_back(make_pair(POINT, this));

    return ret;
}

vector<pair<VarType, Figure*>> Point::intersect(Plane plane) {
    vector<pair<VarType, Figure*>> ret;

    if (withinEps(plane.norm.dot(plane.p - p), 0))
        ret.push_back(make_pair(POINT, this));

    return ret;
}

vector<pair<VarType, Figure*>> Point::intersect(Sphere sphere) {
    vector<pair<VarType, Figure*>> ret;

    if (withinEps((p - sphere.p).mag(), sphere.r))
        ret.push_back(make_pair(POINT, this));

    return ret;
}

vector<pair<VarType, Figure*>> Point::intersect(Empty empty) {
    return empty.intersect(*this);
}

vector<pair<VarType, Figure*>> Point::pointOn() {
    vector<pair<VarType, Figure*>> ret;

    ret.push_back(make_pair(POINT, this));

    return ret;
}

// -------------------------------------------------------------------------------------------------------
// LINE
// -------------------------------------------------------------------------------------------------------

vector<pair<VarType, Figure*>> Line::intersect(Point point) {
    return point.intersect(*this);
}

vector<pair<VarType, Figure*>> Line::intersect(Line line) {
    vector<pair<VarType, Figure*>> ret;

    if (*this == line) {
        ret.push_back(make_pair(LINE, this));
    } else {
        Vector3D v = m.cross(line.p - p);
        if (withinEps(v.dot(line.p + line.m - p), 0)) {
            return ret;
        }

        long double u = ((p - line.p).cross(line.m).mag()) / (m.cross(line.m).mag());
        ret.push_back(make_pair(POINT, new Point(p + (m * u))));
    }

    return ret;
}

vector<pair<VarType, Figure*>> Line::intersect(Circle circle) {
    vector<pair<VarType, Figure*>> ret;

    vector<pair<VarType, Figure*>> sphereIntersection = (*this).intersect(Sphere(circle.p, circle.r));
    for (int i = 0; i < sphereIntersection.size(); i++) {
        Point* intersection = (Point*)sphereIntersection[i].second;
        long double dot = circle.norm.dot((*intersection).p - circle.p);
        if (withinEps(dot, 0))
            ret.push_back(sphereIntersection[i]);
    }
    
    return ret;
}

vector<pair<VarType, Figure*>> Line::intersect(Plane plane) {
    vector<pair<VarType, Figure*>> ret;

    long double dot = (p - plane.p).dot(plane.norm);
    if (withinEps(dot, 0))
        ret.push_back(make_pair(LINE, this));

    return ret;
}

vector<pair<VarType, Figure*>> Line::intersect(Sphere sphere) {
    vector<pair<VarType, Figure*>> ret;

    long double u = m.dot(sphere.p - p) / m.mag2();
    Vector3D c = p + (m * u);
    long double d = (c - sphere.p).mag();
    if (withinEps(d, sphere.r)) {
        ret.push_back(make_pair(POINT, new Point(c)));
        return ret;
    }
    if (d > sphere.r) {
        return ret;
    }
    long double v = sqrt(sphere.r * sphere.r - d * d);
    ret.push_back(make_pair(POINT, new Point(c - (m * v))));
    ret.push_back(make_pair(POINT, new Point(c + (m * v))));

    return ret;
}

vector<pair<VarType, Figure*>> Line::intersect(Empty empty) {
    return empty.intersect(*this);
}

vector<pair<VarType, Figure*>> Line::pointOn() {
    vector<pair<VarType, Figure*>> ret;

    // TODO: try and update this to an exponential distri or smth
    long double r = rand();
    ret.push_back(make_pair(POINT, new Point(p + m * r)));

    return ret;
}

// -------------------------------------------------------------------------------------------------------
// CIRCLE
// -------------------------------------------------------------------------------------------------------

vector<pair<VarType, Figure*>> Circle::intersect(Point point) {
    return point.intersect(*this);
}

vector<pair<VarType, Figure*>> Circle::intersect(Line line) {
    return line.intersect(*this);
}

vector<pair<VarType, Figure*>> Circle::intersect(Circle circle) {
    vector<pair<VarType, Figure*>> ret;

    Sphere s1 = Sphere(p, r);
    Sphere s2 = Sphere(circle.p, circle.r);
    vector<pair<VarType, Figure*>> sphereIntersection = s2.intersect(s1);
    if (sphereIntersection.size() == 0)
        return ret;
    if (sphereIntersection[0].first == POINT) {
        Point* pt = (Point*) sphereIntersection[0].second;
        int dot1 = norm.dot((*pt).p - p);
        int dot2 = circle.norm.dot((*pt).p - circle.p);
        if (withinEps(dot1, 0) && withinEps(dot2, 0))
            return sphereIntersection;
        else
            return ret;
    } else {
        Plane plane = Plane(circle.p, circle.norm);
        vector<pair<VarType, Figure*>> planeIntersection = plane.intersect(*(Circle*)sphereIntersection[0].second);
        for (int i = 0; i < planeIntersection.size(); i++) {
            Point* pt = (Point*) planeIntersection[i].second;
            if (withinEps(norm.dot((*pt).p - p), 0))
                ret.push_back(make_pair(POINT, pt));
        }
    }

    return ret;
}

vector<pair<VarType, Figure*>> Circle::intersect(Plane plane) {
    vector<pair<VarType, Figure*>> ret;

    if (plane == Plane(p, norm)) {
        ret.push_back(make_pair(CIRCLE, this));
    } else {
        if (isZeroVector(plane.norm.cross(norm)))
            return ret;
        Line* line = (Line*) plane.intersect(Plane(p, norm))[0].second;
        ret = (*line).intersect(*this);
    }

    return ret;
}

vector<pair<VarType, Figure*>> Circle::intersect(Sphere sphere) {
    vector<pair<VarType, Figure*>> ret;

    vector<pair<VarType, Figure*>> sphereIntersection = Plane(p, norm).intersect(sphere);
    if (sphereIntersection.size() == 0)
        return ret;
    if (sphereIntersection[0].first == POINT) {
        Point* pt = (Point*) sphereIntersection[0].second;
        if (withinEps(((*pt).p - p).mag(), r))
            ret.push_back(make_pair(POINT, pt));
    } else {
        Circle* circ = (Circle*) sphereIntersection[0].second;
        return (*circ).intersect(*this);
    }

    return ret;
}

vector<pair<VarType, Figure*>> Circle::intersect(Empty empty) {
    return empty.intersect(*this);
}

vector<pair<VarType, Figure*>> Circle::pointOn() {
    vector<pair<VarType, Figure*>> ret;

    // need to implement pointOn() functions for circle,plane,sphere

    return ret;
}

// -------------------------------------------------------------------------------------------------------
// PLANE
// -------------------------------------------------------------------------------------------------------

vector<pair<VarType, Figure*>> Plane::intersect(Point point) {
    return point.intersect(*this);
}

vector<pair<VarType, Figure*>> Plane::intersect(Line line) {
    return line.intersect(*this);
}

vector<pair<VarType, Figure*>> Plane::intersect(Circle circle) {
    return circle.intersect(*this);
}

vector<pair<VarType, Figure*>> Plane::intersect(Plane plane) {
    vector<pair<VarType, Figure*>> ret;

    if (*this == plane) {
        ret.push_back(make_pair(PLANE, this));
    } else {
        Vector3D m = norm.cross(plane.norm);
        if (isZeroVector(m))
            return ret;
        auto randPt = pointOn();
        Point* pt = (Point*) randPt[0].second;
        Line l = Line(p, (*pt).p - p);
        vector<pair<VarType, Figure*>> lineIntersection = l.intersect(*this);
        ret.push_back(make_pair(LINE, new Line((*(Point*)lineIntersection[0].second).p, m)));
    }

    return ret;
}

vector<pair<VarType, Figure*>> Plane::intersect(Sphere sphere) {
    vector<pair<VarType, Figure*>> ret;

    Line l = Line(sphere.p, norm);
    Vector3D c = (*(Point*) l.intersect(*this)[0].second).p;
    long double d = (c - sphere.p).mag();
    if (withinEps(d, sphere.r)) {
        ret.push_back(make_pair(POINT, new Point(c)));
        return ret;
    }
    if (d > sphere.r) {
        return ret;
    }
    ret.push_back(make_pair(CIRCLE, new Circle(c, norm, sqrt(sphere.r * sphere.r - d * d)));
    return ret;
}

vector<pair<VarType, Figure*>> Plane::intersect(Empty empty) {
    return empty.intersect(*this);
}

vector<pair<VarType, Figure*>> Plane::pointOn() {
    vector<pair<VarType, Figure*>> ret;
    //TODO:implement this
    return ret;
}

// -------------------------------------------------------------------------------------------------------
// SPHERE
// -------------------------------------------------------------------------------------------------------

vector<pair<VarType, Figure*>> Sphere::intersect(Point point) {
    return point.intersect(*this);
}

vector<pair<VarType, Figure*>> Sphere::intersect(Line line) {
    return line.intersect(*this);
}

vector<pair<VarType, Figure*>> Sphere::intersect(Circle circle) {
    return circle.intersect(*this);
}

vector<pair<VarType, Figure*>> Sphere::intersect(Plane plane) {
    return plane.intersect(*this);
}

vector<pair<VarType, Figure*>> Sphere::intersect(Sphere sphere) {
    vector<pair<VarType, Figure*>> ret;

    if (*this == sphere) {
        ret.push_back(make_pair(SPHERE, this));
        return ret;
    }
    long double d = (p - sphere.p).mag();
    if (withinEps(d, r + sphere.r)) {
        Vector3D v = (sphere.p - p) * r / (r + sphere.r) + p;
        ret.push_back(make_pair(POINT, new Point(v)));
        return ret;
    }
    if (withinEps(d + r, sphere.r)) {
        Vector3D v = (p - sphere.p) / d * sphere.r + sphere.p;
        ret.push_back(make_pair(POINT, new Point(v)));
        return ret;
    }
    if (withinEps(d + sphere.r, r)) {
        Vector3D v = (sphere.p - p) / d * r + p;
        ret.push_back(make_pair(POINT, new Point(v)));
        return ret;
    }
    if (d > r + sphere.r || r > d + sphere.r || sphere.r > d + r) {
        return ret;
    }
    long double h = 0.5 + (r * r - sphere.r * sphere.r) / (2 * d * d);
    long double r = sqrt(r * r - h * h * d * d);
    Vector3D c = p + (sphere.p - p) * h;
    Vector3D norm = sphere.p - p;
    ret.push_back(make_pair(CIRCLE, new Circle(c, norm, r)));

    return ret;
}

vector<pair<VarType, Figure*>> Sphere::intersect(Empty empty) {
    return empty.intersect(*this);
}

vector<pair<VarType, Figure*>> Sphere::pointOn() {
    vector<pair<VarType, Figure*>> ret;

    return ret;
}

// -------------------------------------------------------------------------------------------------------
// EMPTY
// -------------------------------------------------------------------------------------------------------

vector<pair<VarType, Figure*>> Empty::intersect(Point point) {
    vector<pair<VarType, Figure*>> ret;
    return ret;
}

vector<pair<VarType, Figure*>> Empty::intersect(Line line) {
    vector<pair<VarType, Figure*>> ret;
    return ret;
}

vector<pair<VarType, Figure*>> Empty::intersect(Circle circle) {
    vector<pair<VarType, Figure*>> ret;
    return ret;
}

vector<pair<VarType, Figure*>> Empty::intersect(Plane plane) {
    vector<pair<VarType, Figure*>> ret;
    return ret;
}

vector<pair<VarType, Figure*>> Empty::intersect(Sphere sphere) {
    vector<pair<VarType, Figure*>> ret;
    return ret;
}

vector<pair<VarType, Figure*>> Empty::intersect(Empty empty) {
    vector<pair<VarType, Figure*>> ret;
    return ret;
}

vector<pair<VarType, Figure*>> Empty::intersect(Space space) {
    vector<pair<VarType, Figure*>> ret;
    return ret;
}

vector<pair<VarType, Figure*>> Empty::pointOn() {
    vector<pair<VarType, Figure*>> ret;
    return ret;
}

// -------------------------------------------------------------------------------------------------------
// SPACE
// -------------------------------------------------------------------------------------------------------

vector<pair<VarType, Figure*>> Space::intersect(Point point) {
    vector<pair<VarType, Figure*>> ret;
    ret.push_back(make_pair(POINT, &point));
    return ret;
}

vector<pair<VarType, Figure*>> Space::intersect(Line line) {
    vector<pair<VarType, Figure*>> ret;
    ret.push_back(make_pair(LINE, &line));
    return ret;
}

vector<pair<VarType, Figure*>> Space::intersect(Circle circle) {
    vector<pair<VarType, Figure*>> ret;
    ret.push_back(make_pair(CIRCLE, &circle));
    return ret;
}

vector<pair<VarType, Figure*>> Space::intersect(Plane plane) {
    vector<pair<VarType, Figure*>> ret;
    ret.push_back(make_pair(PLANE, &plane));
    return ret;
}

vector<pair<VarType, Figure*>> Space::intersect(Sphere sphere) {
    vector<pair<VarType, Figure*>> ret;
    ret.push_back(make_pair(SPHERE, &sphere));
    return ret;
}

vector<pair<VarType, Figure*>> Space::intersect(Empty empty) {
    return empty.intersect(*this);
}

vector<pair<VarType, Figure*>> Space::intersect(Space space) {
    vector<pair<VarType, Figure*>> ret;
    ret.push_back(make_pair(SPACE, this));
    return ret;
}

vector<pair<VarType, Figure*>> Space::pointOn() {
    vector<pair<VarType, Figure*>> ret;

    return ret;
}