#include"math.h"

void define_vars() {
    vars.define(variable{"pi", 3.141592653, true});
    vars.define(variable{"e", 2.7182818284, true});
    vars.define(variable{"ans"});
}

long long factorial(long long n) {

    if(n < 0) {
        throw std::runtime_error("Unable to take a factorial of a negative value");
    }

    if(n == 0) {
        return 1;
    };

    for(int i = n - 1; i > 0; i--) {
        n *= i;
    }

    return n;
}
