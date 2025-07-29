#include"PPPheaders.h"
#include <ostream>

int permutation(int a, int b);
int combination(int a, int b);
int factorial(int a);

int main() {


	while(true) {
		int a = 0;
		int b = 0;
		char choice = '\0';

		std::cout<<"Permutation/Combination Calculator"<<std::endl
			<<"Enter two integers or q to quit: ";

		std::cin>>choice;
		if(choice == 'q') {
			return 0;
		}
		std::cin.putback(choice);
		if(!(std::cin>>a)) {
			throw std::runtime_error("Bad Input");
		}
		if(!(std::cin>>b)) {
			throw std::runtime_error("Bad Input");
		}

		std::cout<<"Compute permutation, combination, or both (p/c/b or q to quit): ";
		if(!(std::cin>>choice)) {
				throw std::runtime_error("Bad Input");
		}

		switch(choice) {
			case 'p': case 'P':
				std::cout<<"Permutation = "<<permutation(a, b);
				break;
			case 'c': case 'C':
				std::cout<<"Combination = "<<combination(a, b);
				break;
			case 'b': case 'B':
				std::cout<<"Permutation = "<<permutation(a, b)<<std::endl
					<<"Combination = "<<combination(a, b)<<std::endl;
				break;
			case 'q': case 'Q':
				return 0;
			default:
				throw std::runtime_error("Bad Input");
				break;
		}

	}

	return 0;

}

int factorial(int a) {
	if(a == 0) {
		return 1;
	}
	for(int i = a - 1; i > 1; i--) { 
		a *= i;
	}
	return a;
}

int permutation(int a, int b) {
	return factorial(a) / factorial(a - b);
}

int combination(int a, int b) {
	return permutation(a, b) / factorial(b);
}
