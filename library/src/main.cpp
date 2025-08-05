#include<iostream>
#include<string>
#include<chrono>
#include<vector>
#include<sstream>
#include"book.h"

int main() {
	std::vector<Book> books;

try{
	while(std::cin && !std::cin.eof()) {

	std::string author;
	std::string title;
	std::string ISBN;
	std::string dateStr;
	std::chrono::year_month_day date;

	std::cout<<"Author: ";
	std::getline(std::cin, author);
	std::cout<<"Title: ";
	std::getline(std::cin, title);
	std::cout<<"ISBN (N-N-N-X): ";
	std::getline(std::cin, ISBN);
	std::cout<<"Enter Year (mm/dd/yyyy): ";
	std::getline(std::cin, dateStr);
	std::istringstream dateStream(dateStr);
	std::chrono::from_stream(dateStream, "%D", date);
	books.push_back(Book{ISBN, author, title, date});

	for(Book b : books) {
		std::cout<<b.title()<<std::endl
			<<b.author()<<std::endl
			<<b.copyrightDate()<<std::endl
			<<b.ISBN()<<std::endl;
	}
	}
}
catch(std::exception &e) {
	std::cerr<<e.what()<<std::endl;
}
}
