#include"parser.h"
#include <chrono>
#include <exception>

void parser(std::istream& is, std::vector<Book>& v) {
	//read json file that is is pointed at until EOF, create Book objects from file
	
	const std::string typeField = "\"type\":";
	const std::string bookField = "\"book\",";
	
	is.exceptions(is.exceptions()|std::ios::badbit);

	char c = '\0';
	is>>c;
	if(c != '[') {
		throw std::runtime_error("Illegal JSON File Format");
	}
	while(c != ']') {
		is>>c;
		if(c != '{') {
			throw std::runtime_error("Illegal JSON File Format");
		}

		std::string s;
		is>>s;
		if(s != typeField) {
			throw std::runtime_error{"Expected a \"type\" field"};
		}

		is>>s;
		try{
			if(s != bookField) {
				throw std::runtime_error("Expected type field to be a book");
			}
				v.push_back(book_parser(is));
		}catch(std::exception &e) {
			std::cerr<<"Caught Exception"<<std::endl
				<<"Error: "<<e.what()<<std::endl;
			if(is.bad()) {
				throw std::runtime_error("Input Stream 'is' went to bad state.  Giving up!");
			}
			is.clear();
			char c = '\0';
			while(is && (c != ']' && c != '}')) {
					c = is.get();
			}
			if(c == '}') {
				is.unget();
			} else {
				return;
			}
		}

		is>>c;  //eats }
		is>>c; //eats , or ]

	}
}
void parser(std::istream& is, std::vector<Patron>& v) {
	//read json file that is is pointed at until EOF, create Patron objects as we parse and put them on a vector that is passed by reference
	
	const std::string typeField = "\"type\":";
	const std::string patronField = "\"patron\",";
	
	is.exceptions(is.exceptions()|std::ios::badbit);

	char c = '\0';
	is>>c;
	if(c != '[') {
		throw std::runtime_error("Illegal JSON File Format");
	}
	while(c != ']') {
		is>>c;
		if(c != '{') {
			throw std::runtime_error("Illegal JSON File Format");
		}

		std::string s;
		is>>s;
		if(s != typeField) {
			throw std::runtime_error{"Expected a \"type\" field"};
		}

		is>>s;
		try{
			if(s != patronField) {
				throw std::runtime_error("Expected type to be a patron");
			}
				v.push_back(patron_parser(is));
		}catch(std::exception &e) {
			std::cerr<<"Caught Exception"<<std::endl
				<<"Error: "<<e.what()<<std::endl;
			if(is.bad()) {
				throw std::runtime_error("Input Stream 'is' went to bad state.  Giving up!");
			}
			is.clear();
			char c = '\0';
			while(is && (c != ']' && c != '}')) {
					c = is.get();
			}
			if(c == '}') {
				is.unget();
			} else {
				return;
			}
		}

		is>>c;  //eats }
		is>>c; //eats , or ]

	}
}

Book book_parser(std::istream& is) {

	std::vector<field> fields;
	parseFields(is, fields);
	getUniqueFields(fields);
	return book_creator(fields);
}

void parseFields(std::istream& is, std::vector<field>& fields) {
	do{
		char c;
		field a;
		is>>std::quoted(a.name);
		c = is.get();
		if(c != ':') {
			throw std::runtime_error("Expected ':' after field name");
		}
		is>>std::quoted(a.value);
		if(is.peek() == ',') {
			is.get(); //eat
		}
		do{
			c = is.get(); //eat whitespace
		}while(std::isspace(c));
		is.unget();
		if(c != '"' && c != '}') {
			throw std::runtime_error("Expected start of new field or end of book block");
		}
		fields.push_back(a);
	}while(is && is.peek() != '}');
}

void getUniqueFields(std::vector<field>& v) {
	for(size_t i = 0; i<v.size(); i++) {
		for(size_t j = 0; j<v.size(); j++) {
			if(j != i) {
				if(v[i].name == v[j].name) {
					v.erase(v.begin() + i);
				}
			}
		}
	}
}

Book book_creator(const std::vector<field>& v) {
	constexpr int BOOK_FIELD_SIZE = 5;

	std::string title, author, isbn, genreStr, date;

	if(v.size() != BOOK_FIELD_SIZE) {
		throw std::runtime_error("Need 5 unique fields to define a book but found a different number");
	}
	for(field f : v) {
		if(f.name == "title") {
			title = f.value;
		}
		if(f.name == "author") {
			author = f.value;
		}
		if(f.name == "ISBN") {
			isbn = f.value;
		}
		if(f.name == "genre") {
			genreStr = f.value;
		}
		if(f.name == "copyright") {
			date = f.value;
		}
	}

	if(title.empty() || author.empty() || isbn.empty() || genreStr.empty() || date.empty()) {
		throw std::runtime_error("Need 5 unique fields to define a book but found a different number");
	}
	std::chrono::year_month_day copyrightDate = dateExtractor(date);
	Book::Genre genre = genreExtractor(genreStr);

	return Book{isbn, author, title, genre, copyrightDate};
}

std::chrono::year_month_day dateExtractor(const std::string& str) {
	std::istringstream is {str};
	std::chrono::year_month_day ymd;
	std::chrono::from_stream(is, "%m-%d-%Y", ymd);
	return ymd;
}

Book::Genre genreExtractor(const std::string &str) {
	if(str == "fiction") {
		return Book::Genre::fiction;
	}
	if(str == "non-fiction") {
		return Book::Genre::nonfiction;
	}
	if(str == "periodical") {
		return Book::Genre::periodical;
	}
	if(str == "biography") {
		return Book::Genre::biography;
	}
	if(str == "children") {
		return Book::Genre::children;
	}
	throw std::runtime_error("Failed to extract genre from string!");
}

Patron patron_parser(std::istream& is) {
	std::vector<field> fields;
	parseFields(is, fields);
	getUniqueFields(fields);
	return patron_creator(fields);
}

Patron patron_creator(const std::vector<field>& v) {
	constexpr int PATRON_FIELD_SIZE = 3;

	if(v.size() != PATRON_FIELD_SIZE) {
		throw std::runtime_error("Expected 3 fields to fully define a patron but got a different number!");
	}
	
	std::string name;
	double bal = 0;
	int id = 0;
	bool balDefined = false;
	bool idDefined = false;

	for(field f : v) {
		if(f.name == "ID") {
			f.value.pop_back(); //erase the trailing ,
			id = std::stoi(f.value);
			idDefined = true;
		}
		if(f.name == "bal") {
			f.value.erase(0, 1); //erase the $
			bal = std::stod(f.value);
			balDefined = true;
		}
		if(f.name == "name") {
			name = f.value;
		}
	}

	if(name.empty() || !idDefined || !balDefined) {
		throw std::runtime_error("Expected fields 'ID', 'bal' and 'name' for Patron but didn't get at least one of those fields");
	}
	return Patron{name, id, bal};
}

