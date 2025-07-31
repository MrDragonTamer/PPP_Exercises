#include"PPPheaders.h"
#include"grammer.h"
#include"math.h"

int main() {

try{ 

    define_consts();
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

