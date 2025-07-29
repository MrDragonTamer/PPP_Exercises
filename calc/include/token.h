#ifndef TOKEN
#define TOKEN

class token {
	public:
		char kind = '\0';
		double value = 0;
		token(char k, double d) : kind{k}, value{d} {}
		token(char k) : kind{k} {}
		token() {}
};

#endif
