#ifndef SJTU_PLAN_HPP
#define SJTU_PLAN_HPP
#include "exceptions.hpp"
#include "timer.hpp"

#include <iostream>
#include <cstring>
#include <cstdlib>

namespace sjtu {
	class plan {
	private:
		std::string train;
		int stationNumber,*ticketNumber[4];
		timer startTime;
		bool status;
		static const int TOTAL = 2000;
	public:
		plan() :train(""),startTime(),status(0) {}
		plan(const std::string &_train,const timer &_startTime,const int _stationNumber,const bool &_status = 0)
			:train(_train),startTime(_startTime),stationNumber(_stationNumber),status(_status) {
			for (int i = 1; i <= 3; ++i) ticketNumber[i] = new int[stationNumber + 1];
		}
		plan(const plan &other)
			:train(other.train),startTime(other.startTime),stationNumber(other.stationNumber),status(other.status) {}
		plan & operator=(const plan &other) {
			if (this == &other) return *this;
			train = other.train,startTime = other.startTime,status = other.status;
			return *this;
		}
		std::string getTrain() const{return train;}
		timer getStartTime() const{return startTime;}
		int getStationNumber() const{return stationNumber;}
		bool getStatus() const{return status;}
		int getLeftTickets(int type,int u,int v) const{
			if (u >= v || type < 1 || type > 3) return 0;
			int number = 0;
			for (int i = v - 1; i >= u; --i) number += ticketNumber[type][i];
			return TOTAL - number;
		}
		void modifyStartTime(const timer &newStartTime) {startTime = newStartTime;}
		void modifyStatus(const bool &newStatus) {status = newStatus;}
		void query(int type,int u,int v) const{
			if (u >= v || type < 1 || type > 3) throw invalid_input();
			std::cout << startTime << ' ' << status << ' ' << getLeftTickets(type,u,v) << std::endl;
		}
		void orderTicket(int type,int u,int v) {
			if (u >= v || type < 1 || type > 3 || getLeftTickets(type,u,v) == 0) throw invalid_input();
			for (int i = u; i < v; ++i) ++ticketNumber[type][i];
		}
		void disorederTickey(int type,int u,int v) {
			if (u >= v || type < 1 || type > 3 || getLeftTickets(type,u,v) == 0) throw invalid_input();
			for (int i = u; i < v; ++i) --ticketNumber[type][i];
		}
		friend std::ostream & operator<<(std::ostream &os,
			const plan &obj) {
			os << "train: " << obj.train << std::endl;
			os << "stationNumber: " << obj.stationNumber << std::endl;
			os << "startTime: " << obj.startTime << std::endl;
			os << "status " << obj.status << std::endl;
			os << "ticketNumber:" << std::endl;
			for (int i = 1; i <= 3; ++i) {
				for (int j = 1; j <= obj.stationNumber; ++j) {
					os << obj.ticketNumber[i][j] << ' ';
				}
				os << std::endl;
			}
			return os;
		}
		~plan() {
			if (train != "") {
				for (int i = 1; i <= 3; ++i)
					delete [] ticketNumber[i];
			}
		}
	};
}
#endif
