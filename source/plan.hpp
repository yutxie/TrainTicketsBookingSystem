#ifndef SJTU_PLAN_HPP
#define SJTU_PLAN_HPP

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include "exceptions.hpp"
#include "rwInt.hpp"

namespace sjtu {
	class plan {
	private:
		string train;
		int stationNumber,*ticketNumber[4];
		string startTime;
		int status;
		static const int TOTAL = 2000;
	public:
		plan() :train(""),startTime(),stationNumber(0),status(0) {
			for (int i = 0; i < 3; ++i)
				ticketNumber[i] = NULL;
		}
		plan(const string &_train,const string &_startTime,const int _stationNumber,const int &_status = 0)
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
		const string & getTrain() const{return train;}
		const string & getStartTime() const{return startTime;}
		int getStationNumber() const{return stationNumber;}
		int getStatus() const{return status;}
		int getLeftTickets(int type,int u,int v) const{
			if (status == 0 || u >= v || type < 1 || type > 3) return 0;
			int number = 0;
			for (int i = v - 1; i >= u; --i) number = std::max(number,ticketNumber[type][i]);
			return TOTAL - number;
		}
		void modifyStartTime(const string &newStartTime) {startTime = newStartTime;}
		void modifyStatus(const int &newStatus) {status = newStatus;}
		void query(int type,int u,int v) const{
			std::cout << startTime << ' ' << status << ' ' << getLeftTickets(type,u,v) << std::endl;
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
			for (int i = 1; i <= 3; ++i) {
				if (ticketNumber[i] != NULL)
					delete [] ticketNumber[i];
			}
		}
		friend std::ifstream &operator<<(std::ifstream &file, plan &obj) {
			if(obj.stationNumber) throw container_is_not_empty();
			file << obj.stationNumber;
//			file.read(reinterpret_cast<char *> (&stationNumber), sizeof(int));
			for (int i = 1; i <= 3; ++i) {
				obj.ticketNumber[i] = new int[obj.stationNumber + 1];
				for (int j = 0; j <= obj.stationNumber; ++j)
					file << obj.ticketNumber[i][j];
//					file.read(reinterpret_cast<char *> (&ticketNumber[i][j]), sizeof(int));
			}
			file << obj.train;
			file << obj.startTime;
			file << obj.status;
//			readString(file,train);
//			readString(file,startTime);
//			file.read(reinterpret_cast<char *> (&status), sizeof(int));
			return file;
		}
		friend std::ofstream &operator>>(std::ofstream &file, plan &obj) {
			file >> obj.stationNumber;
//			file.write(reinterpret_cast<char *> (&stationNumber), sizeof(int));
			for (int i = 1; i <= 3; ++i)
				for (int j = 0; j <= stationNumber; ++j)
					file >> obj.ticketNumber[i][j];
//					file.write(reinterpret_cast<char *> (&ticketNumber[i][j]), sizeof(int));
			file >> obj.train;
			file >> obj.startTime;
			file >> obj.status; 
//			writeString(file,train);
//			writeString(file,startTime);
//			file.write(reinterpret_cast<char *> (&status), sizeof(int));
			return file;
		}
	};
}
#endif /*plan_hpp*/
