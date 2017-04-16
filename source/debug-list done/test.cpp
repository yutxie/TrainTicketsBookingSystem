#include <fstream>
#include <iostream>
#include "getPath.hpp"

int main(int argc, char *argv[]) {
	
	std::string filename = getPath(argv[0]) + "test.bin";
	int n = 30;
	std::fstream io;
	io.open(filename, std::fstream::out);
	io.write(reinterpret_cast<const char *> (&n), sizeof(int));
	