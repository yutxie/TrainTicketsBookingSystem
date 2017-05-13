#ifndef SJTU_RWINT_HPP
#define SJTU_RWINT_HPP

#include <cstdio>
#include <iostream>
#include <fstream>

namespace sjtu {
	
	std::ifstream &operator>>(std::ifstream &file, int &x) {
		file.read(reinterpret_cast<char *> (&x), sizeof(int));
		std::cout << x << std::endl;
		return file;
	}
	std::ofstream &operator<<(std::ofstream &file, const int &x) {
		std::cout << x << std::endl;
		file.write(reinterpret_cast<const char *> (&x), sizeof(int));
		return file;
	}
}

#endif