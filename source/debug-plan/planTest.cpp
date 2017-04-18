#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include "plan.hpp"
using namespace std;
int _rand() {return rand() * 32767 + rand();}
int ticket[4][233];
bool status;
int main() {
	srand(time(0));
	string trainName;
	sjtu::timer startTime;
	int stationNumber;
	cin >> trainName >> startTime >> stationNumber;
	sjtu::plan pl(trainName,startTime,stationNumber);
	int n = 5;
	int op,u,v,type,t,ans;
	pl.modifyStatus(1);
	while (n--) {
		op = rand() % 10;
		u = v;
		while (u == v) {
			u = _rand() % stationNumber + 1;
			v = _rand() % stationNumber + 1;
		}
		if (u > v) t = u,u = v,v = t;
		type = _rand() % 3 + 1;
		if (op <= 5) {
			pl.orderTicket(type,u,v);
			for (int i = u; i < v; ++i)
				++ticket[type][i];
		}
		else if (op == 5) {
			pl.disorderTicket(type,u,v);
			for (int i = u; i < v; ++i)
				--ticket[type][i];
		}
		else if (op >= 6) {
			int number = 0;
			for (int i = v - 1; i >= u; --i) number = max(number,ticket[type][i]);
			if (pl.getLeftTickets(type,u,v) != 2000 - number) cout << "WA " << pl.getLeftTickets(type,u,v) << ' ' << 2000 - number << endl;
//			assert(pl.getLeftTickets(type,u,v) == 2000 - number);
		}
	}
	cout << pl;
	return 0;
}
