#include"PPPheaders.h"
#include"grammer.h"

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

