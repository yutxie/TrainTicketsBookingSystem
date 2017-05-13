#ifndef SJTU_STRING_HPP
#define SJTU_STRING_HPP

#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include "exceptions.hpp"

namespace sjtu {

class string {
private:
	std::string str;
public:
	string(const std::string &_str = "") : str(_str) {}
	string(const string &other) : str(other.str) {}
	string(const char *ch) : str(ch) {}
	string &operator=(const string &other) {str = other.str; return *this;}
	string &operator=(const std::string &other) {str =  other; return *this;}
	string &operator=(const char *ch) {str = ch; return *this;}
	string operator+(const string &other) {return string(str + other.str);}
	string &operator+=(const string &other) {return *this = *this + other;}
	string operator+(const char &ch) {return string(str + ch);}
	string operator+=(const char &ch) {return *this = *this + ch;}
	string operator+(const char *ch) {return string(str + ch);}
	string operator+=(const char *ch) {return *this = *this + ch;}
	size_t length() const {return str.length();}
	char operator[](size_t index) const {return str[index];}
	bool operator==(const string &other) const {return str == other.str;}
	bool operator<(const string &other) const {return str < other.str;}
	friend std::ifstream &operator>>(std::ifstream &file, string &str) {
		str = "";
		int length;
		file.read(reinterpret_cast<char *> (&length), sizeof(int));
		for(int i = 0; i < length; ++i) {
			char ch;
			file.read(reinterpret_cast<char *> (&ch), sizeof(char));
			str += ch;
		}
		return file;
	}
	friend std::ofstream &operator<<(std::ofstream &file, const string &str) {
		int length = str.length();
		file.write(reinterpret_cast<const char *> (&length), sizeof(int));
		for(int i = 0; i < length; ++i) {
			char ch = str[i];
			file.write(reinterpret_cast<const char *> (&ch), sizeof(char));
		}
		return file;
	}
};

}

#endif