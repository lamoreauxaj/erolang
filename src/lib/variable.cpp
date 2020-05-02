#include "variable.h"

extern "C" Var ero_write(Var *var) {
    double res = *((double*) &var->val);
    cout << res << endl;
    return Var(UNDEFINED, 0);
}
