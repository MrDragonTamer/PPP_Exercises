#include"PPPheaders.h"
#include <linux/limits.h>

int main() {
    
    std::cout<<"Enter integer: ";

    std::vector<char> digits;

    std::string str;
    std::getline(std::cin, str);

    for(char x : str) {
        switch(x) {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                digits.push_back(x);
                break;
            default:
                std::string str = "Not a digit: ";
                str.push_back(x);
                throw std::runtime_error(str);
        }
    } 

        for(char d : digits) {
            std::cout<<d;
        }

        std::cout<<" is ";

        for(int i = 0; (size_t)i < digits.size(); i++) {
           
            if((size_t)i != 0) {
                std::cout<<" and ";
            }

            std::cout<<digits[i] - '0';

            switch(digits.size() - i) {
                case 4:
                    std::cout<<" thousand";
                    break;
                case 3:
                    std::cout<<" hundred";
                    break;
                case 2:
                    std::cout<<" ten";
                    break;
                case 1:
                    std::cout<<" one";
                    break;
                default: 
                    throw std::runtime_error("Invalid Input");
            }

            if(digits[i] - '0' != 1) {
                std::cout<<"s";
            }

        }

        std::cout<<std::endl;

    return 0;

}
