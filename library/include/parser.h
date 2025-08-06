#pragma once
#include"book.h"
#include"patron.h"
#include<iostream>
#include<sstream>
#include<vector>

struct field{
	std::string name;
	std::string value;
};

void parser(std::istream& is, std::vector<Book>& b, std::vector<Patron>& p);
void parseFields(std::istream& is, std::vector<field>& fields);
Book book_parser(std::istream& is);
Book book_creator(const std::vector<field>& v);
Book::Genre genreExtractor(const std::string& str);
std::chrono::year_month_day dateExtractor(const std::string& str);
Patron patron_parser(std::istream& is);
Patron patron_creator(const std::vector<field>& v);

