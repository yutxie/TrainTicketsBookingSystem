#ifndef SJTU_RWFILE_HPP
#define SJTU_RWFILE_HPP

#include <cstdio>
#include <iostream>
#include <fstream>

namespace std {
	
	template<class T>
	void readIn(std::ifstream &file, T &x) {
		file.read(reinterpret_cast<char *> (&x), sizeof(T));
	}
	template<class T>
	void writeOut(std::ofstream &file, const T &x) {
		file.write(reinterpret_cast<const char *> (&x), sizeof(T));
	}
	
	void readIn(std::ifstream &file, std::string &x) {
		x = "";
		int n;
		readIn(file, n);
		for(int i = 0; i < n; ++i) {
			char ch;
			readIn(file, ch);
			x += ch;
		}
	}
	void writeOut(std::ofstream &file, const std::string &x) {
		int n = x.length();
		writeOut(file, n);
		for(int i = 0; i < n; ++i) {
			char ch = x[i];
			writeOut(file, ch);
		}
	}
}

#endif