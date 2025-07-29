#ifndef GRAMMER
#define GRAMMER
#include"PPPheaders.h"
#include"tokenStream.h"

//functions to seperate parsing grammer
void calculate();
double statement();
double expression();
double term();
double factor();
double primary();
double func();
int factorial(int n); //helper function for primary  

enum class funcNames { SQRT };

extern tokenStream ts;

constexpr std::string prompt = ">";
constexpr std::string result = "=";

#endif
