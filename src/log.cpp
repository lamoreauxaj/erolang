#include "log.h"
using namespace std;

vector<string> messages;

void log_error(string message, int start=-1, int end=-1) {
    string error = "[ERROR]: " + message;
    if (start != -1)
        error += " at " + start
    if (end != -1)
        error += ":" + end;
}

vector<string> get_messages() {
    return messages;
}
