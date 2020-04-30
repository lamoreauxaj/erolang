#include <asm.h>

vector<string> dataSeg;
map<string, vector<string>> functions;

int add_to_function(string name, string text, int line) {
    if (line == -1 || line == functions[name].size()) {
        functions[name].push_back(text);
        return functions.size() - 1;
    } else {
        if (line < -1 || functions.size() < line)
            log_error("out of bounds assembly line");
        functions[name][line] = text;
        return line;
    }
}

string get_function_line(string name, int line) {
    if (!functions.count(name))
        log_error("function has not been defined in assembly");
    if (line < 0 || functions[name].size() <= line)
        log_error("out of bounds assembly line");
    return functions[name][line];
}

int add_to_data(string text) {
    dataSeg.push_back(text);
    return dataSeg.size() - 1;
}

string get_data_line(int line) {
    if (line < 0 || dataSeg.size() <= line)
        log_error("out of bounds data segment");
    return dataSeg[line];
}

void write_assembly(string file) {
    ofstream fileWriter;
    fileWriter.open(file);

    fileWriter << "     .data\n";
    for (string s : dataSeg) {
        fileWriter << s << '\n';
    }
    
    fileWriter << "     .text\n";
    fileWriter << " .extern printf\n";
    fileWriter << "  .global main\n";

    // asdf need to probably update print code (this is just p4 version)
    fileWriter << "print:\n";
    fileWriter << "    lea printformat(%rip), %rdi\n";
    fileWriter << "    mov %r15, %rsi\n";
    fileWriter << "    xor %rax, %rax\n";
    fileWriter << "    call printf\n";
    fileWriter << "    ret\n";

    if (!functions.count("main"))
        log_error("No main function in assembly code");
    
    for (auto p : functions) {
        fileWriter << p.first << ":\n";
        for (string s : p.second) {
            fileWriter << "     " << s << '\n';
        }
        fileWriter << "ret\n";
    }

    fileWriter.close();
}