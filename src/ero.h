#ifndef ERO_H
#define ERO_H
#include <iostream>
#include <string>
#include "asm.h"
#include "compile.h"
#include "lexer.h"
#include "log.h"
#include "parser.h"
using namespace std;

int compile_program(string input_file, string output_file, bool prod=false);

string run_program(string input_file);

int ero_main(int argc, char **argv);

#endif