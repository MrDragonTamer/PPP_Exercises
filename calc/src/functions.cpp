#include"function.h"
#include"grammer.h"

const std::vector<std::string> funcNames = {"sqrt", "pow", "ln", "log"};

double call_func(std::string name) {
    //call a function based on name
    std::vector<double> args;
    parseArgs(args);

    if(name == "sqrt") {
        //sqrt of a (sqrt(a))
        if(args.size() != 1) {
            throw std::runtime_error("Incorrect number of arguments for function " + name);
        }
        return sqrt(args[0]);
    }

    if(name == "pow") {
        //power of a to b (pow(a,b))
        if(args.size() != 2) {
            throw std::runtime_error("Incorrect number of arguments for function " + name);
        }
        return pow(args[0], args[1]);
    }

    if(name == "ln") {
        //natural log of a (ln(a))
        if(args.size() != 1) {
            throw std::runtime_error("Incorrect number of arguments for function " + name);
        }
        return std::log(args[0]);
    }

    if(name == "log") {
        //log base b of a (log(b,a))
        //log(b,a) == log(a) / log(b)
        if(args.size() != 2) {
            throw std::runtime_error("Incorrect number of arguments for function " + name);
        }
        return std::log(args[1]) / std::log(args[0]);
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

