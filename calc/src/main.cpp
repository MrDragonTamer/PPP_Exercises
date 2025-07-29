#include"PPPheaders.h"

#include"token.h"
#include"tokenStream.h"

tokenStream ts;

constexpr std::string prompt = ">";
constexpr std::string answer = "=";


//functions to seperate parsing grammer
void calculate();
void statement();
double expression();
double term();
double primary();

//functions related to handling variables

//misc calculation helper functions
int factorial(int n);



int main() {

try{ 

    calculate();

	return 0;
}

catch(std::exception &e) {
    std::cerr<<e.what()<<std::endl;
}
catch(...) {
    std::cerr<<"An Unhandled Exception Occured"<<std::endl;
}
}

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
    
    double result = expression();
    std::cout<<answer<<result<<std::endl;
}
catch(std::exception &e) {
    std::cerr<<e.what()<<std::endl;
    ts.ignore(token::PRINT);
}
}

double expression() {
    token op;
    
    double lval = term();
    op = ts.get();

    switch(op.kind) {
        case '+':
            lval += term();
            break;
        case '-':
            lval -= term();
            break;
        default:
            ts.putback(op);
            break;
    }
   return lval; 
}

double term() {
    token op;

    double lval = primary();
    op = ts.get();

    switch(op.kind) {
        case '*':
            lval *= primary();
            break;
        case '/':
            {
                double rval = primary();
                if(rval == 0) {
                    throw std::runtime_error("Divide By Zero Error");
                }
                lval /= rval;
                break;
            }
        case '%':
            {
                double d = primary();
                if(d == 0) {
                    throw std::runtime_error("Divide By Zero Error");
                }
                lval = fmod(lval, d);
                break;
            }
        default:
            ts.putback(op);
            break;
    }
    return lval;
}

double primary() {
    token t;
    
    t = ts.get();

    double result = 0;

    switch(t.kind) {
        case token::NUMBER:
            {
                token lookAhead = ts.get();
                if(lookAhead.kind == '!') {
                    t.value = factorial(t.value);
                }
                else {
                    ts.putback(lookAhead);
                }
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
            t = ts.get();
            if(t.kind == '!') {
                result = factorial(result);
            }
            else {
                ts.putback(t);
            }
            break;
        case '{':
            result = expression();
            t = ts.get();
            if(t.kind != '}') {
                throw std::runtime_error("Missing closing parathesis.");
            }
            break;
        default:
            throw std::runtime_error("Invalid Syntax!");
            break;
    }
    return result;
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
