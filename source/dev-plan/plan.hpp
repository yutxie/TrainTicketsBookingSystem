#ifndef SJTU_PLAN_HPP
#define SJTU_PLAN_HPP
#include "exceptions.hpp"
#include "timer.hpp"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>

namespace sjtu {
	class plan {
	private:
		std::string train;
		int stationNumber,*ticketNumber[4];
		timer startTime;
		bool status;
		static const int TOTAL = 2000;
	public:
		plan() :train(""),startTime(),stationNumber(0),status(0) {}
		plan(const std::string &_train,const timer &_startTime,const int _stationNumber,const bool &_status = 0)
			:train(_train),startTime(_startTime),stationNumber(_stationNumber),status(_status) {
			for (int i = 1; i <= 3; ++i) {
				ticketNumber[i] = new int[stationNumber + 1];
				for (int j = 0; j <= stationNumber; ++j)
					ticketNumber[i][j] = 0;
			}
		}
		plan(const plan &other)
			:train(other.train),startTime(other.startTime),stationNumber(other.stationNumber),status(other.status) {
			for (int i = 1; i <= 3; ++i) {
				ticketNumber[i] = new int[stationNumber + 1];
				for (int j = 0; j <= stationNumber; ++j)
					ticketNumber[i][j] = other.ticketNumber[i][j];
			}
		}
		plan & operator=(const plan &other) {
			if (this == &other) return *this;
			for (int i = 1; i <= 3; ++i) {
				if (stationNumber) delete [] ticketNumber[i];
				ticketNumber[i] = new int[stationNumber + 1];
				for (int j = 0; j <= stationNumber; ++j)
					ticketNumber[i][j] = other.ticketNumber[i][j];
			}
			train = other.train,startTime = other.startTime,status = other.status;
			return *this;
		}
		const std::string & getTrain() const{return train;}
		const timer & getStartTime() const{return startTime;}
		int getStationNumber() const{return stationNumber;}
		bool getStatus() const{return status;}
		int getLeftTickets(int type,int u,int v) const{
			if (status == 0 || u >= v || type < 1 || type > 3) return 0;
			int number = 0;
			for (int i = v - 1; i >= u; --i) number = std::max(number,ticketNumber[type][i]);
			return TOTAL - number;
		}
		void modifyStartTime(const timer &newStartTime) {startTime = newStartTime;}
		void modifyStatus(const bool &newStatus) {status = newStatus;}
		void query(int type,int u,int v) const{
			std::cout << startTime << ' ' << status << ' ' << getLeftTickets(type,u,v) << std::endl;
		}
		void orderTicket(int type,int u,int v) {
			if (status == 0 || u >= v || type < 1 || type > 3 || getLeftTickets(type,u,v) == 0) throw invalid_input();
			for (int i = u; i < v; ++i) ++ticketNumber[type][i];
		}
		void disorderTicket(int type,int u,int v) {
			if (status == 0 || u >= v || type < 1 || type > 3 || getLeftTickets(type,u,v) == 0) throw invalid_input();
			for (int i = u; i < v; ++i) {
				if (ticketNumber[type][i] == 0) throw invalid_input();
				--ticketNumber[type][i];
			}
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
		
		void readIn(std::ifstream &file) {
			if(stationNumber) throw container_is_not_empty();
			file.read(reinterpret_cast<char *> (&stationNumber), sizeof(int));
			for (int i = 1; i <= 3; ++i) {
				ticketNumber[i] = new int[stationNumber + 1];
				for (int j = 0; j <= stationNumber; ++j)
					file.read(reinterpret_cast<char *> (&ticketNumber[i][j]), sizeof(int));
			}
			int len;
			file.read(reinterpret_cast<char *> (&len), sizeof(int));
			char trainName[len];
			for (int i = 0; i < len; ++i)
				file.read(reinterpret_cast<char *> (&trainName[i]), sizeof(char));
			train = trainName;
			file.read(reinterpret_cast<char *> (&startTime), sizeof(timer));
			file.read(reinterpret_cast<char *> (&status), sizeof(bool));
		}
		void writeOut(std::ofstream &file) {
			file.write(reinterpret_cast<char *> (&stationNumber), sizeof(int));
			for (int i = 1; i <= 3; ++i)
				for (int j = 0; j <= stationNumber; ++j)
					file.write(reinterpret_cast<char *> (&ticketNumber[i][j]), sizeof(int));
			int len = train.length();
			file.write(reinterpret_cast<char *> (&len), sizeof(int));
			for (int i = 0; i < len; ++i)
				file.write(reinterpret_cast<char *> (&train[i]), sizeof(char));
			file.write(reinterpret_cast<char *> (&startTime), sizeof(timer));
			file.write(reinterpret_cast<char *> (&status), sizeof(bool));
		}
	};
}
#endif
