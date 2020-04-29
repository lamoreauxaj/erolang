#include <asm.h>

vector<string> dataSeg;
map<string, vector<string>> functions;

int add_to_function(string name, string text, int line) {
    if (line == -1 || line == functions[name].size()) {
        functions[name].push_back(text);
        return functions.size() - 1;
    } else {
        if (line < -1 || functions.size() < line)
            log_error("out of bounds assembly line", -1, -1);
        functions[name][line] = text;
        return line;
    }
}

string get_function_line(string name, int line) {
    if (!functions.count(name))
        log_error("function has not been defined in assembly", -1, -1);
    if (line < 0 || functions[name].size() <= line)
        log_error("out of bounds assembly line", -1, -1);
    return functions[name][line];
}

int add_to_data(string text) {
    dataSeg.push_back(text);
    return dataSeg.size() - 1;
}

string get_data_line(int line) {
    if (line < 0 || dataSeg.size() <= line)
        log_error("out of bounds data segment", -1, -1);
    return dataSeg[line];
}

void write_assembly(string file) {

}