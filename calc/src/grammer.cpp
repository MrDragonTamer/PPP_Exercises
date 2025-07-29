#include"PPPheaders.h"
#include"token.h"
#include"tokenStream.h"
#include"grammer.h"
#include"variable.h"

tokenStream ts;


void calculate() {
//evaluate expressions in a loop until quit command is found
while(std::cin) try{
    if(!ts.isFull()) {
        std::cout<<prompt;
    }
    
    token t = ts.get();
    while(t.kind == token::PRINT) {
        t = ts.get(); //eat ;
    }
    if (t.kind == token::QUIT) {
        break;
    }
    ts.putback(t);
    
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
        default:
            ts.putback(t);
            return expression();
    }
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
            if(is_declared(t.name)) {
                return get_value(t.name);
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
    token op = ts.get();

    if(op.kind != token::NAME) {
        throw std::runtime_error("Attempting to call a function without knowing the name of the function!");
    }
    if(op.name == "sqrt") {
        return sqrt(expression());
    }
    throw std::runtime_error(op.name + " is not a valid function!");
}

int factorial(int n) {
    if(n == 0) {
        return 1;
    };

    for(int i = n - 1; i > 0; i--) {
        n *= i;
    }

    return n;
}
