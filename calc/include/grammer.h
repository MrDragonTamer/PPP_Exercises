#ifndef GRAMMER
#define GRAMMER
import std;
#include"tokenStream.h"
#include"math.h"

//functions to seperate parsing grammer
void calculate();
double statement();
double expression();
double term();
double factor();
double primary();
double func();

extern tokenStream ts;

constexpr std::string prompt = ">";
constexpr std::string result = "=";

#endif
