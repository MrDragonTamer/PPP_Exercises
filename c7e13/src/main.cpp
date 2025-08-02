#include<vector>
#include<string>
#include<iostream>
#include<algorithm>

void append_strings(std::vector<std::string>& s);
void lengthOfStrings(const std::vector<std::string>& v, std::vector<int>& s);
std::string longestString(const std::vector<std::string>& s, const std::vector<int>& v);
std::string smallestString(const std::vector<std::string>& s, const std::vector<int>& v);
std::string firstLexagraphicString(const std::vector<std::string>& v);
std::string lastLexagraphicString(const std::vector<std::string>& v);

int main() {

	std::cout<<"Enter strings followed by newline"<<std::endl;

	std::string s;
	std::vector<std::string> str;
	append_strings(str);
	std::vector<int> strSizes;
	lengthOfStrings(str, strSizes);

	for(size_t i = 0; i<str.size(); i++) {
		std::cout<<"Length of \""<<str[i]<<"\" is "<<strSizes[i]<<std::endl;
	}

	s = smallestString(str, strSizes);	
	std::cout<<"The smallest string was \""<<s<<"\" with a size of "<<s.size()<<std::endl;
	s = longestString(str, strSizes);
	std::cout<<"The longest string was \""<<s<<"\" with a size of "<<s.size()<<std::endl;
	
	s = firstLexagraphicString(str);
	std::cout<<"The first string by alphabetical order was \""<<s<<"\" with a size of "<<s.size()<<std::endl;
	s = lastLexagraphicString(str);
	std::cout<<"The last string by alphabetical order was \""<<s<<"\" with a size of "<<s.size()<<std::endl;

	return 0;

}

void append_strings(std::vector<std::string>& v) {
	std::string s;
	while(std::cin && !std::cin.eof()) {
		std::cin>>s;
		if(!std::cin.eof()) {
			v.push_back(s);
		}
	}
	return;
}

void lengthOfStrings(const std::vector<std::string>& v, std::vector<int>& s) {
	for(std::string x : v) {
		s.push_back(x.size());
	}
}

std::string longestString(const std::vector<std::string>& s, const std::vector<int>& v) {
	int max = 0;
	int pos = 0;
	for(size_t i = 0; i<s.size(); i++) {
		if(v[i] > max) {
			pos = i;
			max = v[i];
		}
	}
	return s[pos];
}

std::string smallestString(const std::vector<std::string>& s, const std::vector<int>& v) {
	int min = v[0];
	int pos = 0;
	for(size_t i = 1; i<s.size(); i++) {
		if(v[i] < min) {
			min = v[i];
			pos = i;
		}
	}
	return s[pos];
}

std::string firstLexagraphicString(const std::vector<std::string>& s) {
	std::vector<std::string> temp = s;
	std::sort(temp.begin(), temp.end());
	return temp[0];
}

std::string lastLexagraphicString(const std::vector<std::string>& s) {
	std::vector<std::string> temp = s;
	std::sort(temp.begin(), temp.end());
	return temp[temp.size() - 1];
}
