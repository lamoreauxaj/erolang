#include <iostream>
#include "asm.h"
#include "compile.h"
#include "lexer.h"
#include "log.h"
#include "parser.h"
using namespace std;

string read_program(string file) {
    string res;
    ifstream in(file);
    string line;
    while (getline(in, line)) res += line + "\n";
    return res;
}

int main(int argc, char **argv) {

    return ero_main(argc, argv);

    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <input> <output>\n";
        return 1;
    }

    bool prod = argc > 3;

    string input_file = argv[1];
    string output_file = argv[2];

    string program = read_program(input_file);

    system(string("rm " + output_file + ".s").c_str());
    system(string("rm " + output_file).c_str());

    cout << "compiling" << endl;
    vector<Token> tokens = tokenize(program);
    for (Token t : tokens) {
        cout << t.type << ":" << t.text << " ";
    }
    cout << "\n";
    Stmts *tree = parse(tokens);
    cout << pprinter(tree) << "\n";
    int res = 0;
    if (!tree) res = 1;
    if (!res) {
        compile(tree);
        // add_to_function("main", "xor %rax, %rax");
        // add_to_function("main", "ret");
        write_assembly(output_file + ".s");

        string command;
        if (prod)
            command = "g++ -static -o " + output_file + " " + output_file + ".s ./variable.o ./geometry.o";
        else
            command = "g++ -static -o " + output_file + " " + output_file + ".s ../src/lib/variable.cpp ../src/lib/geometry.cpp";
        int rc = system(command.c_str());
        if (rc) {
            cout << "unable to compile" << endl;
            res = 1;
        }
    }

    for (string error : get_messages()) {
        cout << error << "\n";
    }

    return res;
}