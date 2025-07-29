#ifndef TOKEN_STREAM
#define TOKEN_STREAM

#include"token.h"

class tokenStream {
	public:
		token get();
		void putback(token t);
		bool isFull();
		void ignore(char c);
	private:
		bool full = false;
		token buffer{'\0','\0'};
		bool isDigit(char c);
};

#endif
