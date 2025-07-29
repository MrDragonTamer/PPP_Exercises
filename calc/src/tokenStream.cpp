#include"../include/tokenStream.h"
#include"../include/PPPheaders.h"

void tokenStream::putback(token t) {
	if(full) {
        throw std::runtime_error("Attempted to putback a token into a full TokenStream");
	}

    full = true;

    buffer = t;

};

bool tokenStream::isFull() {
    return full;
}

void tokenStream::ignore(char c) {
    //discard tokens and chars from tokenStream and cin until we find c
    
    if(full && c == buffer.kind) {
        full = false;
        return;
    }

    char ch = '\0';
    while(std::cin>>ch) {
        if(ch == c) {
            return;
        }
    }
}

token tokenStream::get() {
    
    if(full) {
        full = false;
        return buffer;
    }

    char x = '\0';
    std::cin>>x;
    switch (x) {
        case token::PRINT: case token::QUIT:
        case '(': case ')': 
        case '{': case '}':
        case '*': case '/': case '+': case '-':
        case '!': case '%':
            return token{x};
            break;
/*        case '-':
            std::cin>>x;
            std::cin.putback(x);
            if(isDigit(x)) { //negative number
                std::cin.putback('-');
                double t = 0;
                std::cin>>t;
                return token{'8', t};
            }
            else { //subtraction sign
                return token{'-'};
            } */
        case '0': case '1': case '2': case '3': case '4': 
        case '5': case '6': case '7': case '8': case '9':
        case '.':
            {
            std::cin.putback(x);
            double t = 0;
            std::cin>>t;
            return token{token::NUMBER, t};
            break;
            }
        default:
            throw std::runtime_error("Invalid Token!");
    }
}

bool tokenStream::isDigit(char c) {
    if(c >= '0' && c <= '9') {
        return true;
    }
    return false;
}
