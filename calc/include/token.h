#ifndef TOKEN
#define TOKEN

import std;

class token {
	public:
		char kind = '\0';
		double value = 0;
		std::string name = "";
		
		token(char k, std::string str) : kind{k}, name{str} {}
		token(char k, double d) : kind{k}, value{d} {}
		token(char k) : kind{k} {}
		token() {}

		enum type { 
			NUMBER = '8',
			QUIT = 'q',
			PRINT = ';',
			HELP = 'h',
			NAME = 'a',
			DECLARATION_KEYWORD = 'L'
		};
};

#endif
