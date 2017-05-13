#ifndef SJTU_SYSTEM_HPP
#define SJTU_SYSTEM_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include "rwFile.hpp"
#include "exceptions.hpp"
#include "user.hpp"
#include "ticket.hpp"
#include "train.hpp"
#include "map.hpp"
#include "log.hpp"

namespace sjtu {
	
	class system {
		
		class no_such_station : public exception {
        public:
            no_such_station() : exception(
                "no_such_station",
                "No such station!"
            ) {}
        };
		
	private:
		std::string password;
		map<std::string,train> trainList;
		map<std::string,user> userList;
		map<std::pair<int,int>,list<std::string> > trainMap;
		map<int,std::string> stationName;
		map<std::string,int> stationId;
		log systemLog;
		int count;
		std::string int_to_string(int v) {
			std::string str;
			while (v) {str += char(v % 10);v /= 10;}
			for(int i = 0, j = str.length() - 1; i < j; ++i) std::swap(str[i], str[j]);
			return str;
		}
	public:
		system() :password("000000"),trainList(),userList(),trainMap(),stationName(),stationId(),systemLog(),count(0) {systemLog.open("log.txt");}
		const std::string getPassword() const {return password;}
		/*void getTrainTicketList(std::ostream &os) {
			int sz = trainList.size();
			if (sz < 2) os << "There is " << sz << "train" << std::endl;
			else os << "There are " << sz << "trains" << std::endl;
			map<std::string,train> ::iterator it;
			int cnt = 1;
			for (it = trainList.begin(); it != trainList.end(); ++it,++cnt) {
				os << "Train No." << cnt << std::endl;
				os << it -> second;
			}
		}*/
		train & getTrain(const std::string &trainId) {
			if (trainList.find(trainId) == trainList.end()) throw invalid_input();
			return trainList[trainId];
		}
		map<std::string,user> &getUserList() {return userList;}
		user & getUser(const std::string &userId) {
			if (userList.find(userId) == userList.end()) throw invalid_input();
			return userList[userId];
		}
		void modifyPassword(const std::string &newPassword) {
			std::string str = "Change password from " + password + " to " + newPassword;
			systemLog.add(str);
			password = newPassword;
		}
		void insertTrain(const train &_train) {
			std::string _trainId = _train.getId(),_stationName;
			/*
			int pos;
			if ((pos = _trainId.find('/')) >= 0) {
				trainList[_trainId.substr(0,pos)] = trainList[_trainId.substr(pos + 1,_trainId.length() - pos - 1] = _train;
			}
			*/
			trainList[_trainId] = _train;
			int sz = _train.getStationList().size(),u,v;
			for (int i = 0; i < sz; ++i) {
				std::string _stationName = _train.getStation(i).getName();
				if (stationId.find(_stationName) == stationId.end()) {
					stationId[_stationName] = stationId.size();
					stationName[stationId.size()] = _stationName;
				}
			}
			for (int i = 0; i < sz; ++i) {
				u = stationId[_train.getStation(i).getName()];
				for (int j = i + 1; j < sz; ++j) {
					v = stationId[_train.getStation(j).getName()];
					trainMap[std::pair<int,int>(u,v)].push_back(_trainId);
				}
			}
			std::string str = "Insert train " + _train.getId();
			systemLog.add(str);
		}
		void deleteTrain(const std::string &trainId) {
			train _train = trainList[trainId];
			map<std::string,train> ::iterator it;
			/*
			int pos;
			if ((pos = trainId.find('/')) >= 0) {
				it = trainList.find(trainId.substr(0,pos));trainList.erase(it);
				it = trainList.find(trainId.substr(pos + 1,trainId.length() - pos - 1));trainList.erase(it);
			}
			*/
			int sz = _train.getStationList().size(),u,v;
			for (int i = 0; i < sz; ++i) {
				u = stationId[_train.getStation(i).getName()];
				for (int j = i + 1; j < sz; ++j) {
					v = stationId[_train.getStation(j).getName()];
					auto it = trainMap[std::make_pair(u,v)].begin();
					for (; it != trainMap[std::make_pair(u,v)].end() && trainId != (*it); ++it);
					trainMap[std::make_pair(u,v)].erase(it);
				}
			}
			it = trainList.find(trainId);trainList.erase(it);
			std::string str = "Delete train " + _train.getId();
			systemLog.add(str);
		}
		void insertUser(const user &_user) {
			userList.insert(make_pair(_user.getId(), _user));
			std::string str = "Insert user " + _user.getId();
			systemLog.add(str);
		}
		void deleteUser(const std::string &userId) {
			std::string str = "Delete user " + userId;
			systemLog.add(str);
			map<std::string,user> ::iterator it;
			it = userList.find(userId);userList.erase(it);
		}
		bool loginAsAdmin(const std::string &_password) const {return _password == password;}
		void initialize() {
			password = "000000";
			trainList.clear();
			userList.clear();
			trainMap.clear();
			stationName.clear();
			stationId.clear();
			std::string str = "Initialize!";
			systemLog.add(str);
		}
		/*
		void importTrain(std::ifstream &file) {
			std::string str;
			while ((file >> str) > 0) {
				
			}
		}
		*/
		list<std::string> query(const std::string &departStation,const std::string &stopStation,const std::string &departDate) {
			if (stationId.find(departStation) == stationId.end() || stationId.find(stopStation) == stationId.end()) throw no_such_station();
			int u = stationId[departStation],v = stationId[stopStation];
			return trainMap[std::pair<int,int>(u,v)];
		}
		int getTicketPrice(const std::string &departStation,const std::string &stopStation,const train &_train,const int &type) const {
			int u = stationId[departStation],v = stationId[stopStation];
			if (u >= v) throw invalid_input();
			int price = _train.getStation(v).getPrice(type) - _train.getStation(u).getPrice(type);
			return price;
		}
		/*const ticket & orderTicket(user &_user,const std::string &trainId,const std::string departDate,
			const std::string &departStation, const std::string &stopStation, int type,const int &number) {
			train _train = trainList[trainId];
			int u = _train.getStationId(departStation),v = _train.getStationId(stopStation);
			std::string departTime = _train.getStation(u).getDepartTime(),stopTime = _train.getStation(v).getStopTime();
			std::string id;
			int ID = ++count,i = 10;
			id = "";
			while (ID) {--i;id += char(ID % 10);ID /= 10;}
			for (; i; --i) id += "0";
			int price = _train.getStation(v).getPrice(type) - _train.getStation(u).getPrice(type);
			// plan
			ticket _ticket(id,trainId,_user.getId(),_user.getName(),departStation,stopStation,departTime,stopTime,type,price,number);
			_train.getPlan(departDate).orderTicket(type,u,v,number);
			// user
			_user.orderTicket(_ticket);
			std::string str = "User " + _user.getId() + " ordered " + int_to_string(number) + " ticket(s) of " + trainId;
			systemLog.add(str);
			return _ticket;
		}*/
		/*void disorderTicket(const ticket &_ticket, int number) {
			train &_train = getTrain(_ticket.getTrain());
			int u = _train.getStationId(_ticket.getDepartStation()),v = _train.getStationId(_ticket.getStopStation());
			_train.getPlan(_ticket.getStartDate()).disorderTicket(_ticket.getType(),u,v,number);
			user &_user = getUser(_ticket.getUserId());
			_user.disorderTicket(_ticket.getId(), number);
			std::string str = "User " + _user.getId() + " disordered " + int_to_string(number) + " ticket(s) of " + _ticket.getTrain();
			systemLog.add(str);
		}*/
		bool loginAsUser(const std::string &userId,const std::string &userPossword) {return userPossword == getUser(userId).getPassword();}
		user & signUpUser(const std::string &userId,const std::string &userPassword,const std::string &userName) {
			std::string str = "Sign up a user " + userId;
			systemLog.add(str);
			userList[userId] = user(userId,userName,userPassword);
			return userList[userId];
		}
		/*
		void work(const std::string &str) {
			
		}
		*/
		friend void readIn(std::ifstream &file, system &obj) {
			readIn(file,obj.password);
			readIn(file,obj.trainList);
			readIn(file,obj.userList);
			readIn(file,obj.trainMap);
			readIn(file,obj.stationName);
			readIn(file,obj.stationId);
			//readIn(file,obj.systemLog);
			obj.count = 0;
		}
		friend void writeOut(std::ofstream &file, system &obj) {
			writeOut(file,obj.password);
			writeOut(file,obj.trainList);
			writeOut(file,obj.userList);
			writeOut(file,obj.trainMap);
			writeOut(file,obj.stationName);
			writeOut(file,obj.stationId);
			//writeOut(file,obj.systemLog);
		}
	};
}
#endif
