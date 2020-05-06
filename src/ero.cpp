#include "ero.h"

string read_file(string file) {
    string res;
    ifstream in(file);
    string line;
    while (getline(in, line)) res += line + "\n";
    return res;
}

int compile_program(string input_file, string output_file, bool prod) {
    string asm_file = output_file + ".s";
    int ret_code = 0;

    log_info("starting compilation");
    vector<Token> tokens = tokenize(program);
    Stmts *tree = parse(tokens);
    if (tree) {
        compile(tree);
        write_assembly(asm_file);

        string command = "g++ -static -o " + output_file + " " + asm_file + " ../src/variable.cpp ../src/geometry.cpp";

        if (system(command.c_str())) {
            log_error("unable to compile");
            ret_code = 1;
        }
    }
    else {
        log_error("unable to parse");
        ret_code = 1;
    }

    show_logs();
    return ret_code;
}

string run_program(string input_file) {
}

int ero_main(int argc, char **argv) {

}
