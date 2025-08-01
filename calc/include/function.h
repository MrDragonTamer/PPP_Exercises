#ifndef FUNCTION
#define FUNCTION

#include<string>
#include<vector>
#include<cmath>
#include"token.h"
#include"tokenStream.h"

double call_func(std::string name);
void parseArgs(std::vector<double>& args);

extern const std::vector<std::string> funcNames;

#endif
