#include"PPPheaders.h"
#include"token.h"
#include"tokenStream.h"
#include"grammer.h"
#include"variable.h"
#include"function.h"
#include"init.h"

tokenStream ts;


void calculate() {
//evaluate expressions in a loop until quit command is found
while(std::cin) try{

    token t;
    
    if(ts.empty()) {
        std::cout<<prompt;
    } else {
        t = ts.get();
        if(t.kind == token::PRINT) {
            std::cout<<prompt;
        }
        ts.putback(t);
    }
    
    t = ts.get();

    while(t.kind == token::PRINT) {
        t = ts.get(); //eat ;
    }
    if(t.kind == token::QUIT) {
//        ts.putback(t);
        break;
    }
    
    if(t.kind == token::HELP) {
        print_help();
        std::cout<<std::endl;
        return calculate();

    } else {
        ts.putback(t);
    }
    
    std::cout<<result<<statement()<<std::endl;
}
catch(std::exception &e) {
    std::cerr<<e.what()<<std::endl;
    ts.ignore(token::PRINT);
}
}

double statement() {
    token t = ts.get();
    switch(t.kind) {
        case token::DECLARATION_KEYWORD:
            return declaration();
            break;
        case token::NAME:
            if(vars.is_declared(variable{t.name})) {
                ts.putback(t);
                return assignment();
            }
            else{
                ts.putback(t);
                return expression();
            }
            break;
        default:
            ts.putback(t);
            return expression();
    }
}

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
    
    std::string name = t.name;

    double value = expression();
    t = ts.get();
    if(t.name == "as") {
        t = ts.get();
        if(t.name == "constant") {
            vars.define(variable{name, value, true});
            return value;
        }
    }

    ts.putback(t);
    vars.define(variable{name, value, false});
    return value;
}

double assignment() {
    token t = ts.get();
    if(t.kind != token::NAME) {
        throw std::runtime_error("Expected variable name for assignment!");
    }
    token op = ts.get();
    if(op.kind != '=') {
        //expresion started with a defined variable but this isn't a assignment statement
        ts.putback(t);
        ts.putback(op);
        return expression();
    }
    return vars.set_value(variable{t.name, expression()});
}

double expression() {
    
    double lval = term();
    token op = ts.get();

    while(true) {
        switch(op.kind) {
            case '+':
                lval += term();
                op = ts.get();
                break;
            case '-':
                lval -= term();
                op = ts.get();
                break;
            default:
                ts.putback(op);
                return lval;
                break;
        }
    }
}

double term() {

    double lval = factor();
    token op = ts.get();
    
    while(true) {
        switch(op.kind) {
            case '*':
                lval *= factor();
                op = ts.get();
                break;
            case '/':
                {
                    double rval = factor();
                    if(rval == 0) {
                        throw std::runtime_error("Divide By Zero Error");
                    }
                    lval /= rval;
                    op = ts.get();
                    break;
                }
            case '%':
                {
                    double d = factor();
                    if(d == 0) {
                        throw std::runtime_error("Divide By Zero Error");
                    }
                    lval = fmod(lval, d);
                    op = ts.get();
                    break;
                }
            default:
                ts.putback(op);
                return lval;
                break;
        }
    }
}

double factor() {
    double lval = primary();

    token op = ts.get();
    while(true) {
        if(op.kind == '!') {
           lval = factorial(lval);
           op = ts.get();
        }
        else {
            ts.putback(op);
            return lval;
        }
    }
}


double primary() {
    
    token t = ts.get();

    double result = 0;

    switch(t.kind) {
        case token::NUMBER:
            {
                return t.value;
                break;
            }
        case '+':
            return primary();
        case '-': 
            return - primary(); //will allow negative factorials
        case '(':
            result = expression();
            t = ts.get();
            if(t.kind != ')') {
                throw std::runtime_error("Missing closing parathesis.");
            }
            break;
        case '{':
            result = expression();
            t = ts.get();
            if(t.kind != '}') {
                throw std::runtime_error("Missing closing parathesis.");
            }
            break;
        case token::NAME:
            if(vars.is_declared(t.name)) {
                return vars.get_value(t.name);
            }
            ts.putback(t);
            return func();
            break;
        default:
            throw std::runtime_error("Invalid Syntax!");
            break;
    }
    return result;
}

double func() {
    //implement grammer of calling functions from calculator
    token op = ts.get();

    if(op.kind != token::NAME) {
        throw std::runtime_error("Attempting to call a function without knowing the name of the function!");
    }
    
    std::string funcName = op.name;
    op = ts.get();
    if(op.kind != '(') {
        ts.putback(op);
        throw std::runtime_error("Missing '(' for function.");
    }

    double value = call_func(funcName);

    op = ts.get();
    if(op.kind != ')') {
        ts.putback(op);
        throw std::runtime_error("Missing ')' for function.");
    }

    return value;
}
