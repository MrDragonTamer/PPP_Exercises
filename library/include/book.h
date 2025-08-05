#pragma once
#include<string>
#include<chrono>

class Book { 
	public:
		Book(std::string ISBN, std::string author, std::string title, std::chrono::year_month_day copyright);
		std::string author() const;
		std::string title() const;
		std::string ISBN() const;
		std::chrono::year_month_day copyrightDate() const;

		std::string author(std::string newAuthor);
		std::string title(std::string newTitle);
		std::string ISBN(std::string newISBN);
		std::chrono::year_month_day copyrightDate(std::chrono::year_month_day newDate);

	private:

		bool valid_ISBN(std::string ISBN) const;

		std::string _ISBN;
		std::string _author;
		std::string _title;
		std::chrono::year_month_day _copyright;
		//std::chrono::year_month_day copyright = std::chrono::year(2020)/std::chrono::February/std::chrono::day(30);
};
