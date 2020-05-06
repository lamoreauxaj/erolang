#ifndef ERROR_H
#define ERROR_H
#include <cstdio>
#include <cstdlib>
#include "variable.h"
using namespace std;

extern "C" void ero_error(const char *msg);

void type_check(Var *arg, VarType type, const char *msg=nullptr);

#endif