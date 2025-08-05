#include"book.h"
#include <chrono>

Book::Book(std::string ISBN, std::string author, std::string title, std::chrono::year_month_day copyright)
	:_author(author), _title(title)
{
	if(valid_ISBN(ISBN) && copyright.ok()) {
		_ISBN = ISBN;
		_copyright = copyright;
			return;
	}
			throw std::runtime_error("Bad Book Initialization");
}

bool Book::valid_ISBN(std::string ISBN) const {
	//check ISBN is of type N-N-N-X where n is an integer and x is a digit or letter
	size_t pos = 0;
	char x = ISBN[pos];
	for(int i = 0; i < 3; i++) {
		while(std::isdigit(x)) {
			pos++;
			x = ISBN[pos];
		}
		if(x != '-' || pos == 0) {
			return false;
		}
		pos++;
		x = ISBN[pos];
	}

	if(!std::isdigit(x) && !std::isalpha(x)) {
		return false;
	}
	if(pos != ISBN.size() - 1) {
		return false;
	}

	return true;
}

std::string Book::author() const {
	return _author;
}
std::string Book::title() const {
	return _title;
}
std::string Book::ISBN() const {
	return _ISBN;
}
std::chrono::year_month_day Book::copyrightDate() const {
	return _copyright;
}

std::string Book::author(std::string newAuthor) {
	_author = newAuthor;
	return _author;
}
std::string Book::title(std::string newTitle) {
	_title = newTitle;
	return _title;
}
std::string Book::ISBN(std::string newISBN) {
	if(valid_ISBN(newISBN)) {
		_ISBN = newISBN;
		return _ISBN;
	}
	throw std::runtime_error("Invalid ISBN");
}
std::chrono::year_month_day Book::copyrightDate(std::chrono::year_month_day newDate) {
	if(newDate.ok()) {
		_copyright = newDate;
		return _copyright;
	}
	throw std::runtime_error("Invalid year_month_day for book");
}
