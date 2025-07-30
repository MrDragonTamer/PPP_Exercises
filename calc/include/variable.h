#ifndef VARIABLE
#define VARIABLE

#include"PPPheaders.h"
#include"tokenStream.h"

class variable {
	public:
		std::string name;
		double value;
};

class symbolMap {
	public:
		double define_var(variable v);
		double set_value(variable v);
		double get_value(variable v);
		bool is_declared(variable v);
	private:
		std::vector<variable> varList;
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
