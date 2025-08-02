#ifndef FUNCTION
#define FUNCTION

import std;
#include"token.h"
#include"tokenStream.h"

double call_func(std::string name);
void parseArgs(std::vector<double>& args);

extern const std::vector<std::string> funcNames;

#endif
