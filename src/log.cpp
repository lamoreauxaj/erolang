#include "log.h"
using namespace std;

vector<string> log_messages;

void log_error(string message, int start, int end) {
    string error = "[ERROR]: " + message;
    if (start != -1)
        error += " at " + start;
    if (end != -1)
        error += ":" + end;
    log_messages.push_back(error);
}

void log_info(string message, int start, int end) {
    string info = "[INFO]: " + message;
    if (start != -1)
        info += " at " + start;
    if (end != -1)
        info += ":" + end;
    log_messages.push_back(info);
}

vector<string> get_messages() {
    return log_messages;
}

void show_logs() {
    for (string log : log_messages) {
        cerr << log << endl;
    }
}
