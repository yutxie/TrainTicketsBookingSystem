class timer {
	int yy, mm, dd;
	int hh, ss;
public:
	timer(int _yy = 0, int _mm = 0, int _dd = 0, int _hh = 0, int _ss = 0) 
		: yy(_yy), mm(_mm), dd(_dd), hh(_hh), ss(_ss) {}
	void standerdize() {}
	timer add(const timer &other) {}
	timer sub(const timer &other) {}
	friend bool operator == (const timer &obj1, const timer &obj2) {}
	friend bool operator < (const timer &obj1, const timer &obj2) {}
	friend bool operator > (const timer &obj1, const timer &obj2) {}
};