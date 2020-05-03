#include "variable.h"

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
