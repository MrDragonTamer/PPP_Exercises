#include<iostream>
#include<string>
#include<chrono>
#include<vector>
#include<sstream>
#include<limits>
#include"book.h"

Book::Genre get_genre();

int main() {
	std::vector<Book> books;

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
	Book::Genre genre = get_genre();
	std::cout<<"Enter Year (mm/dd/yyyy): ";
	std::getline(std::cin, dateStr);
	std::istringstream dateStream(dateStr);
	std::chrono::from_stream(dateStream, "%D", date);
	books.push_back(Book{ISBN, author, title, genre, date});

	for(Book b : books) {
		std::cout<<b<<std::endl;
	}
	}
}

Book::Genre get_genre() {
	std::cout<<"Pick a genre\n"
		<<"1. Fiction\n"
		<<"2. Non-Fiction\n"
		<<"3. Periodical\n"
		<<"4. Biography\n"
		<<"5. Children"<<std::endl;
		int x = 0;

	do{
		std::cout<<"Enter number: ";
		std::cin>>x;
		if(std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}while(x<1 || x>5);

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	switch(x) {
		case 1:
			return Book::Genre::fiction;
		case 2:
			return Book::Genre::nonfiction;
		case 3:
			return Book::Genre::periodical;
		case 4:
			return Book::Genre::biography;
		case 5:
			return Book::Genre::children;
		default:
			throw std::runtime_error("Exited loop without a valid selection");
	}
}
