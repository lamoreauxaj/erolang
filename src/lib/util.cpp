#include "util.h"

double as_double(uint64_t v) {
    return *((double*) &v);
}