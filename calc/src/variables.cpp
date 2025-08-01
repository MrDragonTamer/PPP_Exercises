#include"PPPheaders.h"
#include"grammer.h"
#include"variable.h"

symbolMap vars;

std::string variable::name() const {
    return var_name;
}

double variable::get_value() const {
    return value;
}

double variable::set_value(double x) {
    if(constant) {
        throw std::runtime_error("Attempted to modify variable that was defined as constant!");
    }
    value = x;
    return value;
}

bool variable::isConst() const{
    return constant;
}

bool reserved_name(std::string name) {
    for(std::string s : funcNames) {
        if(name == s) {
            return true;
        }
    }
    return false;
}

double symbolMap::define(variable v) {
    //store variable value after ensure new variable is unique
    
    if(reserved_name(v.name())) {
        throw std::runtime_error(v.name() + " is a reserved name!");
    }
    
    if(is_declared(v)) {
        std::string error = v.name() + " is already a defined variable!";
        throw std::runtime_error(error);
    }
    varList.push_back(v);
    return v.get_value();
}

bool symbolMap::is_declared(variable x) {
    for(const variable& v : varList) {
        if(v.name() == x.name()) {
            return true;
        }
    }
    return false;
}

double symbolMap::set_value(variable x) {
    for(variable& v : varList) {
        if(v.name() == x.name()) {
            v.set_value(x.get_value());
            return v.get_value();
        }
    }
    throw std::runtime_error("Attempted to change value of undefined variable!");
}

double symbolMap::get_value(variable x) {
    for(const variable& v : varList) {
        if(v.name() == x.name()) {
            return v.get_value();
        }
    }
    throw std::runtime_error("Attempted to read value of undefined variable!");
}
