#ifndef VARIABLE
#define VARIABLE

#include"PPPheaders.h"
#include"tokenStream.h"

class variable {
	public:
		std::string name;
		double value;
};

extern tokenStream ts;
extern std::vector<variable> varList;

double declaration();
double assignment();
bool is_declared(std::string var_name);
double define_var(std::string var_name, double value);
double set_value(std::string var_name, double value);
double get_value(std::string var_name);

#endif
