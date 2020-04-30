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

    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <input> <output>\n";
        return 1;
    }

    string input_file = argv[1];
    string output_file = argv[2];

    string program = read_program(input_file);

    cout << "compiling" << endl;
    vector<Token> tokens = tokenize(program);
    Node *tree = parse(tokens);
    compile(tree);
    // add_to_function("main", "xor %rax, %rax");
    // add_to_function("main", "ret");
    write_assembly(output_file + ".s");

    string command = "gcc -static -o " + output_file + " " + output_file + ".s";
    int rc = system(command.c_str());
    if (rc) {
        cout << "unable to compile" << endl;
        return 1;
    }

    return 0;
}