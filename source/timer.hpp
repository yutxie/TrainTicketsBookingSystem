#ifndef SJTU_TIMER_HPP
#define SJTU_TIMER_HPP

#include <iostream>
#include "exceptions.hpp"

namespace sjtu {
	
class timer {
	int yy, mm, dd;
	int hh, ss;
public:
	
	timer(int _yy = 0, int _mm = 0, int _dd = 0, int _hh = 0, int _ss = 0) 
		: yy(_yy), mm(_mm), dd(_dd), hh(_hh), ss(_ss) {}
	friend std::istream & operator>> (std::istream &is, 
		timer &obj) {
		is >> obj.yy >> obj.mm >> obj.dd >> obj.hh >> obj.ss;
		return is;
	}
	friend std::ostream & operator<< (std::ostream &os,
		const timer &obj) {
		//if(yy)
			os << obj.yy << '/' << obj.mm << '/' << obj.dd << ' '
				<< obj.hh << ':' << obj.dd << std::endl;
		//else os << hh << ':' << dd << std::endl;
		return os;
	}
	friend timer operator- (const timer &obj1, const timer &obj2) {
		// be careful when use it
		timer rtn;
		if(obj1 <= obj2) throw exception();
		if(obj1.mm != obj2.mm) {
			rtn.dd = obj1.dd;
			if(obj1.mm % 2) rtn.dd += 31 - obj2.dd;
			else rtn.dd += 30 - obj2.dd;
		} else rtn.dd = obj1.dd - obj2.dd;
		rtn.hh = obj1.hh - obj2.hh;
		rtn.ss = obj1.ss - obj2.ss;
		if(rtn.hh < 0) rtn.hh += 24, --rtn.dd;
		if(rtn.ss < 0) rtn.ss += 60, --rtn.dd;
		return rtn.dd;
	}
	friend bool operator == (const timer &obj1, const timer &obj2) {
		if(obj1.yy != obj2.yy) return false;
		if(obj1.mm != obj2.mm) return false;
		if(obj1.dd != obj2.dd) return false;
		if(obj1.hh != obj2.hh) return false;
		if(obj1.ss != obj2.ss) return false;
		return true;
	}
	friend bool operator < (const timer &obj1, const timer &obj2) {
		if(obj1.yy < obj2.yy) return true;
		if(obj1.mm < obj2.mm) return true;
		if(obj1.dd < obj2.dd) return true;
		if(obj1.hh < obj2.hh) return true;
		if(obj1.ss < obj2.ss) return true;
		return false;
	}
	friend bool operator > (const timer &obj1, const timer &obj2) {
		if(obj1 == obj2 || obj1 < obj2) return false;
		return true;
	}
	friend bool operator <= (const timer &obj1, const timer &obj2) {
		return obj1 < obj2 || obj1 == obj2;
	}
	friend bool operator >= (const timer &obj1, const timer &obj2) {
		return obj1 > obj2 || obj1 == obj2;
	}
};

}

#endif