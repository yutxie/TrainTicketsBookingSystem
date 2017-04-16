#ifndef SJTU_EXCEPTIONS_HPP
#define SJTU_EXCEPTIONS_HPP

#include <cstddef>
#include <cstring>
#include <string>

namespace sjtu {

class exception {
protected:
	const std::string variant = "";
	std::string detail = "";
public:
	exception() {}
	exception(const std::string &_variant, const std::string &_detail) :
		variant(_variant), detail(_detail) {}
	exception(const exception &ec) : variant(ec.variant), detail(ec.detail) {}
	virtual std::string what() {
		return variant + " " + detail;
	}
};

/**
 * TODO
 * Please complete them.
 */
class index_out_of_bound : public exception {
	index_out_of_bound() : exception(
		"index_out_of_bound",
		"Index out of bound!"
		) {}
};

class runtime_error : public exception {
	runtime_error() : exception(
		"runtime_error",
		"Runtime error!"
		) {}
};

class invalid_iterator : public exception {
	invalid_iterator() : exception(
		"invalid_iterator",
		"Invalid iterator!"
		) {}
};

class container_is_empty : public exception {
	container_is_empty() : exception(
		"container_is_empty",
		"Container is empty!"
		) {}
};

class container_is_not_empty : public exception {
	container_is_not_empty() : exception(
		"container_is_not_empty",
		"Container is not empty!"
		) {}
};

class invalid_input : public exception {
public:
	invalid_input() : exception(
		"invalid_input",
		"Invalid input!"
		) {}
};

class no_such_file : public exception {
public:
	no_such_file() : exception(
		"no_such_file",
		"There is no such file to open up!"
		) {}
};

}
#endif
