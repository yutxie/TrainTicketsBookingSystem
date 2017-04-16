#ifndef SJTU_GETPATH_HPP
#define SJTU_GETPATH_HPP

#include <iostream>
#include <cstdio>
#include <string>
#include "exceptions.hpp"

namespace sjtu {

std::string getPath(const std::string &fileName) {
	std::string rtn = fileName;
	while(!rtn.empty() && rtn.back() != '\\') rtn.pop_back();
	if(rtn.empty()) throw invalid_input();
	return rtn;
}

}

#endif