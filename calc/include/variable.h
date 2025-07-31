#ifndef VARIABLE
#define VARIABLE

#include"PPPheaders.h"
#include"tokenStream.h"

class variable {
	public:
		double get_value() const;
		double set_value(double x);
		bool isConst() const;
		std::string name() const;

		variable(std::string str, double v, bool isConst) : var_name(str), value(v), constant(isConst) {}
		variable(std::string str, double v) : var_name(str), value(v) {}
		variable(std::string str) : var_name(str) {}
	private:
		std::string var_name;
		double value = 0;
		bool constant = false;
};

class symbolMap {
	public:
		double define(variable v);
		double set_value(variable v);
		double get_value(variable v);
		bool is_declared(variable v);
	private:
		std::vector<variable> varList;
};

extern tokenStream ts;
extern symbolMap vars;

double declaration();
double assignment();

#endif
