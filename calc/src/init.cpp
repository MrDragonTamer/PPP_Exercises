#include"init.h"

void initialize() {
    define_vars();
    print_welcome_message();
    return;
}

void print_welcome_message() {
    std::cout<<"CALCULATOR V1\tBY TYLER COOPER"<<std::endl
        <<"Enter an expression followed by '"<<char(token::PRINT)<<"'. '"<<char(token::QUIT)<<"' to quit. '"<<char(token::HELP)<<"' for help."<<std::endl;
    return;
}

void print_help() {
    std::cout<<"Calculator V1"<<std::endl
        <<"Usage:"<<std::endl
        <<"Expression;"<<std::endl
        <<"Expression; Expression; ... Expression;"<<std::endl
        <<"Function(expression, ..., expression);"<<std::endl
        <<"let var = expression;"<<std::endl
        <<"let var = expression as constant;"<<std::endl
        <<"var = expression;"<<std::endl
        <<"VARIABLES"<<std::endl
        <<"Use 'let var = expression;' to define a variable var for use in other expressions"<<std::endl
        <<"Use 'let var = expression as constant;' to define a variable var for use in other expressions whose value cannot be overwritten"<<std::endl
        <<"FUNCTIONS"<<std::endl
        <<"Defined functions are: ";
    for(std::string s : funcNames) {
        std::cout<<s;
        if(s != *funcNames.end()) {
            std::cout<<", ";
        }
    }
    std::cout<<"Square Root: sqrt(expression);"<<std::endl
        <<"Power of a to b: pow(a,b); Where a and b are expressions"<<std::endl
        <<"Natural log: ln(expression);"<<std::endl
        <<"Log base b of a: log(b,a); Where a and b are expressions"<<std::endl
        <<std::endl<<"For more help on the syntax of the calculator, see grammer.txt";
    return;
}
