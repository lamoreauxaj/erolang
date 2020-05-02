#ifndef COMPILE_H
#define COMPILE_H
#include <map>
#include <string>
#include <queue>
#include <vector>
#include "asm.h"
#include "lexer.h"
#include "lib/variable.h"
#include "parser.h"
#include "scope.h"
using namespace std;

void compile(Stmts *tree);

#endif