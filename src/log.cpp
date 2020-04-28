#include "log.h"
using namespace std;

vector<string> log_messages;

void log_error(string message, int start, int end) {
    string error = "[ERROR]: " + message;
    if (start != -1)
        error += " at " + start;
    if (end != -1)
        error += ":" + end;
}

vector<string> get_messages() {
    return log_messages;
}
