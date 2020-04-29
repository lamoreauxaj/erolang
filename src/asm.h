#ifndef ASM_H
#define ASM_H
#include <map>
#include <string>
#include <vector>
#include <log.h>
using namespace std;

/**
 * Set of utility functions for writing assembly. These are used during compilation
 * and generating the outputted assembly.
 */

/**
 * Create a function in our assembly.
 * @param name the name of the function
 */
void add_function(string name);

/**
 * Add a line to a given function.
 * @param name the name of the function
 * @param text the text to add
 * @param line which line number to add to
 */
int add_to_function(string name, string text, int line=-1);

/**
 * Get a given line from a function.
 * @param name the name of the function
 * @param line the line number to read (0-indexed)
 */
string get_function_line(string name, int line);

/**
 * Add a given line of text to the data segment.
 * @param text the text to add
 */
int add_to_data(string text);

/**
 * Get a given line from the data segment.
 * @param line the line number to read (0-indexed)
 */
string get_data_line(int line);

/**
 * Write the assembly that has been logged into file
 */
void write_assembly(string file);

#endif