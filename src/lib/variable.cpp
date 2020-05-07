#include "variable.h"

extern "C" Var ero_write(Var *var) {
    if (var->type == REALV) {
        double res = *((double*) &var->val);
        cout << res << endl;
    }
    else if (var->type == BOOL) {
        cout << (var->val ? "true" : "false") << endl;
    }
    else if (var->type == UNDEFINED) {
        cout << "undefined" << endl;
    }
    else if (var->type == POINT || var->type == LINE || var->type == SEGMENT ||
        var->type == RAY || var->type == PLANE || var->type == PLANE ||
        var->type == CIRCLE || var->type == ARC || var->type == SPHERE ||
        var->type == EMPTY || var->type == SPACE) {
        ero_write_geometry(var);
    }
    else {
        ero_error("write: unknown type of variable");
        // should throw runtime error here
    }
    // cout << "hello world!" << endl;
    return Var(UNDEFINED, 0);
}

extern "C" Var ero_equals(Var *a, Var *b) {
    if (a->type != b->type) return Var(BOOL, 0);
    if (a->type == REALV) {
        return Var(BOOL, abs(as_double(a->val) - as_double(b->val)) < EPS);
    }
    else if (a->type == BOOL) {
        return Var(BOOL, a->val == b->val);
    }
    else {
        // not comparable yet
    }
    return Var(UNDEFINED, 0);
}
