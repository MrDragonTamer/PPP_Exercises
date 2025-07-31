#include"function.h"
#include"grammer.h"

double call_func(std::string name) {
    //call a function based on name
    std::vector<double> args;
    parseArgs(args);

    if(name == "sqrt") {
        if(args.size() != 1) {
            throw std::runtime_error("Incorrect number of arguments for function " + name);
        }
        return sqrt(args[0]);
    }

    if(name == "pow") {
        if(args.size() != 2) {
            throw std::runtime_error("Incorrect number of arguments for function " + name);
        }
        return pow(args[0], args[1]);
    }

    throw std::runtime_error("Unrecognized function " + name);
}


void parseArgs(std::vector<double>& args) {
    //parse args of a function and return vector of doubles representing values of expressions

    token t;
    while(t.kind != ')') {
        args.push_back(expression());
       t = ts.get();
       if(t.kind != ',' && t.kind != ')') {
           throw std::runtime_error("Error parsing args for function");
       }
    }
    ts.putback(t);
}

