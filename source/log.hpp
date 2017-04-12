#ifndef SJTU_LOG_HPP
#define SJTU_LOG_HPP 

#include <iostream>
#include <cstdio>
#include <fstream>
#include "exceptions.hpp"

namespace sjtu {
class log {
	std::string fileName;
	std::fstream io;
public:
	log() {}
	log(const std::string &_fileName) : fileName(_fileName) {
		io.open(fileName);
		if(!io) throw no_such_file();
	}
	~log() {
		io.close();
	}
	void clear() {
		if(!io) throw no_such_file();
		io.open(fileName, std::fstream::trunc);
	}
	friend std::ostream & operator<< (std::ostream &os, log &lg) {
		if(!lg.io) throw no_such_file();
		lg.io.seekg(0, lg.io.beg);
		char ch;
		while(lg.io >> ch) os << ch;
		return os;
	}
	void add(const std::string &username, const std::string &opt) {
		if(!io) throw no_such_file();
		io.seekp(0, io.end);
		io << username << ' ' << opt << '.' << std::endl;
	}
};

}

#endif