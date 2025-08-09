#include<iostream>
#include<string>
#include<chrono>
#include<vector>
#include<sstream>
#include<limits>
#include<fstream>
#include"book.h"
#include"patron.h"
#include"parser.h"

int main() {
	std::ifstream books{"./assets/books.json"};
	std::ifstream patrons{"./assets/patrons.json"};
	if(!books || !patrons) {
		throw std::runtime_error("Unable to open ifstream");
	}
	std::vector<Book> a;
	std::vector<Patron> b;
	parser(books, a);
	parser(patrons, b);
	std::cout<<a[0]<<"\n"<<a.size()<<std::endl;
	std::cout<<b.size()<<std::endl;
	return 0;
}
