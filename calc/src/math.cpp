#include"math.h"

void define_consts() {
    vars.define(variable{"pi", 3.141592653, true});
    vars.define(variable{"e", 2.7182818284, true});
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
