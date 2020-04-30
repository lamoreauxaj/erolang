#ifndef COMPILE_H
#define COMPILE_H
#include <map>
#include <string>
#include <queue>
#include <vector>
#include "lexer.h"
#include "parser.h"
#include "variable.h"
using namespace std;

void compile(Node *tree);

#endif