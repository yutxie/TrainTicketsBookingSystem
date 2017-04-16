#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include "getPath.hpp"
#include "list.hpp"

int main(int argc, char *argv[]) {
	
	std::string fileName = sjtu::getPath(argv[0]) + "test.bin";
	
	// int n = 30;
	// std::fstream io;
	// io.open(fileName, std::fstream::out);
	// io.write(reinterpret_cast<const char *> (&n), sizeof(int));
	// for(int i = 0; i < n; ++i)
		// io.write(reinterpret_cast<const char *> (&i), sizeof(int));
	// io.close();
	// io.open(fileName, std::fstream::in);
	// io.read(reinterpret_cast<char *> (&n), sizeof(int));
	// std::cout << n << std::endl;
	// for(int i = 0, x; i < n; ++i) {
		// io.read(reinterpret_cast<char *> (&x), sizeof(int));
		// std::cout << x << std::endl;
	// }
	sjtu::list<int> lst;
	lst.readIn(fileName);
	std::cout << lst.back();
	// for(int i = 30; i < 60; ++i) lst.push_back(i);
	// lst.writeOut(fileName);
	
	return 0;
}