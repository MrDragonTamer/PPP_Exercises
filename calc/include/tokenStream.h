#ifndef TOKEN_STREAM
#define TOKEN_STREAM

#include<queue>
#include"token.h"

class tokenStream {
	public:
		token get();
		void putback(token t);
		bool empty();
		void ignore(char c);
	private:
		std::queue<token> buffer;
		bool isDigit(char c);
};

#endif
