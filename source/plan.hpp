#ifndef SJTU_PLAN_HPP
#define SJTU_PLAN_HPP

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include "exceptions.hpp"
#include "rwFile.hpp"

namespace sjtu {
	class plan {
	private:
		std::string train;
		std::string startDate;
		int stationNumber,*ticketNumber[4];
		int status;
		static const int TOTAL = 2000;
	public:
		plan() :train(""),startDate(),stationNumber(0),status(0) {
			for (int i = 0; i < 3; ++i)
				ticketNumber[i] = NULL;
		}
		plan(const std::string &_train,const std::string &_startDate,const int _stationNumber,const int &_status = 0)
			:train(_train),startDate(_startDate),stationNumber(_stationNumber),status(_status) {
			for (int i = 1; i <= 3; ++i) {
				ticketNumber[i] = new int[stationNumber + 1];
				for (int j = 0; j <= stationNumber; ++j)
					ticketNumber[i][j] = 0;
			}
		}
		plan(const plan &other)
			:train(other.train),startDate(other.startDate),stationNumber(other.stationNumber),status(other.status) {
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
			train = other.train,startDate = other.startDate,status = other.status;
			return *this;
		}
		const std::string & getTrain() const{return train;}
		const std::string & getStartDate() const{return startDate;}
		int getStationNumber() const{return stationNumber;}
		int getStatus() const{return status;}
		int getLeftTickets(int type,int u,int v) const{
			if (status == 0 || u >= v || type < 1 || type > 3) return 0;
			int number = 0;
			for (int i = v - 1; i >= u; --i) number = std::max(number,ticketNumber[type][i]);
			return TOTAL - number;
		}
		void modifyStartDate(const std::string &newStartDate) {startDate = newStartDate;}
		void modifyStatus(const int &newStatus) {status = newStatus;}
		void query(int type,int u,int v) const{
			std::cout << startDate << ' ' << status << ' ' << getLeftTickets(type,u,v) << std::endl;
		}
		void orderTicket(int type,int u,int v,int number) {
			if (status == 0 || u >= v || type < 1 || type > 3 || getLeftTickets(type,u,v) == 0) throw invalid_input();
			for (int i = u; i < v; ++i) ticketNumber[type][i] += number;
		}
		void disorderTicket(int type,int u,int v,int number) {
			if (status == 0 || u >= v || type < 1 || type > 3 || getLeftTickets(type,u,v) == 0) throw invalid_input();
			for (int i = u; i < v; ++i) {
				if (ticketNumber[type][i] == 0) throw invalid_input();
				ticketNumber[type][i] -= number;
			}
		}
		friend std::ostream & operator<<(std::ostream &os,
			const plan &obj) {
			os << "train: " << obj.train << std::endl;
			os << "stationNumber: " << obj.stationNumber << std::endl;
			os << "startDate: " << obj.startDate << std::endl;
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
			for (int i = 1; i <= 3; ++i) {
				if (ticketNumber[i] != NULL)
					delete [] ticketNumber[i];
			}
		}
		friend void readIn(std::ifstream &file, plan &obj) {
			if(obj.stationNumber) throw container_is_not_empty();
			readIn(file,obj.stationNumber);
			for (int i = 1; i <= 3; ++i) {
				obj.ticketNumber[i] = new int[obj.stationNumber + 1];
				for (int j = 0; j <= obj.stationNumber; ++j)
					readIn(file,obj.ticketNumber[i][j]);
			}
			readIn(file,obj.train);
			readIn(file,obj.startDate);
			readIn(file,obj.status);
		}
		friend void writeOut(std::ofstream &file, plan &obj) {
			writeOut(file,obj.stationNumber);
			for (int i = 1; i <= 3; ++i)
				for (int j = 0; j <= obj.stationNumber; ++j)
					writeOut(file,obj.ticketNumber[i][j]);
			writeOut(file,obj.train);
			writeOut(file,obj.startDate);
			writeOut(file,obj.status);
		}
	};
}
#endif /*plan_hpp*/
