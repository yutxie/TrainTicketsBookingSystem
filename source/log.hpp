#ifndef SJTU_LOG_HPP
#define SJTU_LOG_HPP 

#include <iostream>
#include <cstdio>
#include <fstream>
#include "exceptions.hpp"

namespace sjtu {
class log {
	
	class no_such_file : public exception {
	public:
		no_such_file() : exception(
			"no_such_file",
			"There is no such file to open up!"
			) {}
	};
	
	std::string fileName;
	std::fstream io;
public:
	log() {
		fileName = "";
	}
	~log() {
		if(io) io.close();
	}
	void open(const std::string &_fileName) {
		io.open(fileName = _fileName);
		if(!io) throw no_such_file();
	}
	void close() {
		if(!io) throw no_such_file();
		io.close();
	}
	void clear() {
		if(!io) throw no_such_file();
		io.close();
		io.open(fileName, std::fstream::in | std::fstream::out | 
			std::fstream::trunc);
	}
	friend std::ostream & operator<< (std::ostream &os, log &lg) {
		if(!lg.io) throw no_such_file();
		lg.io.seekg(0, lg.io.beg);
		char ch;
		while(lg.io.get(ch)) os.put(ch);
		return os;
	}
	void add(const std::string &str) {
		if(!io) throw no_such_file();
		io.seekp(0, io.end);
		io << str + '\n';
	}
};

}

#endif