#include"PPPheaders.h"
#include"grammer.h"
#include"variable.h"
#include"token.h"

std::vector<variable> varList;

double declaration() {
    //handle variable declaration from grammer
    //assumes we already saw the DECLARATION_KEYWORD
    
    token t = ts.get();
    if(t.kind != token::NAME) {
        throw std::runtime_error("Expected variable name after DECLARATION_KEYWORD");
    }
    
    if(ts.get().kind != '=') {
        throw std::runtime_error("Expected '=' after variable name");
    }
    
    double value = expression();
    define_var(t.name, value);
    return value;
}

double assignment() {
    token t = ts.get();
    if(t.kind != token::NAME) {
        throw std::runtime_error("Expected variable name for assignment!");
    }

    if(ts.get().kind != '=') {
        throw std::runtime_error("Expected '=' after variable name");
    }
    return set_value(t.name, expression());
}
    

double define_var(std::string var_name, double value) {
    //store variable value after ensure new variable is unique
    
    if(is_declared(var_name)) {
        std::string error = var_name + " is already a defined variable!";
        throw std::runtime_error(error);
    }
    varList.push_back(variable{var_name, value});
    return value;
}

bool is_declared(std::string var_name) {
    for(const variable& v : varList) {
        if(v.name == var_name) {
            return true;
        }
    }
    return false;
}

double set_value(std::string var_name, double value) {
    for(variable& v : varList) {
        if(v.name == var_name) {
            v.value = value;
            return value;
        }
    }
    throw std::runtime_error("Attempted to change value of undefined variable!");
}

double get_value(std::string var_name) {
    for(const variable& v : varList) {
        if(v.name == var_name) {
            return v.value;
        }
    }
    throw std::runtime_error("Attempted to read value of undefined variable!");
}
