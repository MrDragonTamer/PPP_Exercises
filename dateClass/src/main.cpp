#include<iostream>

class Date {
	public:
		Date(int y, int m, int d);
		void add_day(int n);
		int year() { return y; }
		int month() { return m; }
		int day() { return d; }

		class invalid{};
	private:
		int y, m, d;
};

Date::Date(int y, int m, int d)
	:y(y), m(m), d(d)
{
	if(m<1 || m>12) {
		throw Date::invalid();
	}
}

int main() {
try{
	std::cout<<"Year: ";
	int y;
	std::cin>>y;
	std::cout<<"Month: ";
	int m;
	std::cin>>m;
	std::cout<<"Day: ";
	int d;
	std::cin>>d;

	Date today{y, m, d};
	throw std::runtime_error("");
	return 0;
}
catch(Date::invalid) {
	std::cout<<"Caught an invalid Date exception!"<<std::endl;
}
catch(...) {
	std::cout<<"Caught a general exception"<<std::endl;
}
}
