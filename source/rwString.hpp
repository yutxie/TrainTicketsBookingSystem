#ifndef SJTU_GETPATH_HPP
#define SJTU_GETPATH_HPP

#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include "exceptions.hpp"

namespace sjtu {

void readString(std::ifstream &file, std::string &str) {
	str = "";
	int length;
	file.read(reinterpret_cast<char *> (&length), sizeof(int));
	for(int i = 0; i < length; ++i) {
		char ch;
		file.read(reinterpret_cast<char *> (&ch), sizeof(char));
		str += ch;
	}
}

void writeString(std::ofstream &file, const std::string &str) {
	int length = str.length();
	file.write(reinterpret_cast<const char *> (&length), sizeof(int));
	for(int i = 0; i < length; ++i) {
		char ch = str[i];
		file.write(reinterpret_cast<const char *> (&ch), sizeof(char));
	}
}

}

#endif