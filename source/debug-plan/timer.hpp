#ifndef SJTU_TIMER_HPP
#define SJTU_TIMER_HPP

#include <iostream>
#include "exceptions.hpp"

namespace sjtu {
	
class timer {
	
	class invalid_time_interval : public exception {
	public:
		invalid_time_interval() : exception(
			"invalid_time_interval",
			"Invalid time interval!"
			) {}
	};
	
	int yy, mm, dd;
	int hh, ss; // ss stands for minute
public:
	
	timer(int _yy = 0, int _mm = 0, int _dd = 0, int _hh = 0, int _ss = 0) 
		: yy(_yy), mm(_mm), dd(_dd), hh(_hh), ss(_ss) {}
	friend std::istream & operator>>(std::istream &is, timer &obj) {
		std::cout << "Please enter the time like: 2017 04 16 16 21, which stands for 2017/04/16 16:21\n";
		is >> obj.yy >> obj.mm >> obj.dd >> obj.hh >> obj.ss;
		return is;
	}
	friend std::ostream & operator<<(std::ostream &os, const timer &obj) {
			os << "time: ";
			os << obj.yy << '/' << obj.mm << '/' << obj.dd << ' '
				<< obj.hh << ':' << obj.ss << std::endl;
		return os;
	}
	timer operator-(const timer &other) const {
		// be careful when use it
		timer rtn;
		if(*this <= other) throw invalid_time_interval();
		if(mm != other.mm) {
			rtn.dd = dd;
			if(mm % 2) rtn.dd += 30 - other.dd;
			else rtn.dd += 31 - other.dd;
		} else rtn.dd = dd - other.dd;
		rtn.hh = hh - other.hh;
		rtn.ss = ss - other.ss;
		while(rtn.ss < 0) rtn.ss += 60, --rtn.hh;
		while(rtn.hh < 0) rtn.hh += 24, --rtn.dd;
		return rtn;
	}
	bool operator==(const timer &other) const {
		if(yy != other.yy) return false;
		if(mm != other.mm) return false;
		if(dd != other.dd) return false;
		if(hh != other.hh) return false;
		if(ss != other.ss) return false;
		return true;
	}
	bool operator<(const timer &other) const {
		if(yy > other.yy) return false;
		else if(yy < other.yy) return true;
		if(mm > other.mm) return false;
		else if(mm < other.mm) return true;
		if(dd > other.dd) return false;
		else if(dd < other.dd) return true;
		if(hh > other.hh) return false;
		else if(hh < other.hh) return true;
		if(ss > other.ss) return false;
		else if(ss < other.ss) return true;
		return false;
	}
	bool operator>(const timer &other) const {
		if(*this == other || *this < other) return false;
		return true;
	}
	bool operator<=(const timer &other) const {
		return *this < other || *this == other;
	}
	bool operator>=(const timer &other) const {
		return *this > other || *this == other;
	}
};

}

#endif
