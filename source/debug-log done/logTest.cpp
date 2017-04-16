#include <iostream>
#include <cstdio>
#include <string>
#include "log.hpp"
#include "getPath.hpp"

int main(int argc, char *argv[]) {
	
	std::string fileName = sjtu::getPath(argv[0]) + "test.txt";
	//std::cout << fileName << std::endl;
	sjtu::log lg;
	lg.open(fileName);
	lg.clear();
	lg.add("test");
	lg.add("finally completed");
	std::cout << lg;
	
	return 0;
}