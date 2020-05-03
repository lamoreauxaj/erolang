#include "geometry.h"

vector<pair<VarType, Figure>> Line::intersect(Point point) {
    vector<pair<VarType, Figure>> ret;
    Vector3D norm = (p - point.p).cross(m);
    if (withinEps(norm.x, 0) && withinEps(norm.y, 0) && withinEps(norm.z, 0))
        ret.push_back(make_pair(POINT, point));
    return ret;
}

vector<pair<VarType, Figure>> Line::intersect(Line line) {
    vector<pair<VarType, Figure>> ret;

    return ret;
}

vector<pair<VarType, Figure>> Line::intersect(Circle circle) {
    vector<pair<VarType, Figure>> ret;

    return ret;
}

vector<pair<VarType, Figure>> Line::intersect(Plane plane) {
    vector<pair<VarType, Figure>> ret;

    return ret;
}

vector<pair<VarType, Figure>> Line::intersect(Sphere sphere) {
    vector<pair<VarType, Figure>> ret;

    return ret;
}

vector<pair<VarType, Figure>> Line::pointOn() {
    vector<pair<VarType, Figure>> ret;

    return ret;
}