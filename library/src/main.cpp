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
	std::ifstream ifs{"./assets/books.json"};
	std::vector<Book> a;
	std::vector<Patron> b;
	parser(ifs, a, b);
	std::cout<<a[0]<<"\n"<<a.size()<<std::endl;
	return 0;
}
