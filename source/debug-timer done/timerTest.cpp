#include "timer.hpp"
#include <iostream>

int main() {
	
	sjtu::timer t1, t2;
	std::cin >> t1 >> t2;
	std::cout << t1 << t2;
	std::cout << t2 - t1;
	
	return 0;
}