#include "variable.h"

static double as_double(uint64_t v) {
    return *((double*) &v);
}

extern "C" Var ero_write(Var *var) {
    if (var->type == REALV) {
        double res = *((double*) &var->val);
        cout << res << endl;
    }
    else if (var->type == BOOL) {
        cout << (var->val ? "true" : "false") << endl;
    }
    else {
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
