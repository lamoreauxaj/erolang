#include "error.h"

extern "C" void ero_error(const char *msg) {
    printf("%s\n", msg);
    exit(1);
}

void type_check(Var *arg, VarType type, const char *msg) {
    if (arg->type != type) {
        if (msg) {
            ero_error(msg);
        }
    }
}
