#ifndef LOG_H
#define LOG_H
#include <string>
#include <vector>
using namespace std;

void log_error(string message, int start=-1, int end=-1);

vector<string> get_messages();

#endif