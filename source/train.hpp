#ifndef SJTU_TRAIN_HPP
#define SJTU_TRAIN_HPP

#include <iostream>
#include <cstdio>
#include "vector.hpp"
#include "map.hpp"
#include <fstream>
#include "station.hpp"
#include "exceptions.hpp"
#include "plan.hpp"
#include "string.hpp"

namespace sjtu {

class train {
	
	class no_such_plan : public exception {
	public:
		no_such_plan() : exception(
			"no_such_plan",
			"No such plan!"
			) {}
	};
	
	class invalid_station : public exception {
	public:
		invalid_station() : exception(
			"invalid_station",
			"Invalid station!"
			) {}
	};
	
	class no_such_station : public exception {
	public:
		no_such_station() : exception(
			"no_such_station",
			"No such station!"
			) {}
	};
	
	class existed_plan : public exception {
	public:
		existed_plan() : exception (
			"existed_plan",
			"Existed plan!"
			) {}
	};
	
private:
	string id;
	string seat[4];
	vector<station> stationList;
	map<string, plan> planList;
	map<string,int> num;
public:
	train() {}
	train(const string &_id) : id(_id) {}
	train(const train &other) :id(other.id),stationList(other.stationList),planList(other.planList),num(other.num) {
		for (int i = 1; i <= 3; ++i)
			seat[i] = other.seat[i];
	}
	train & operator=(const train &other) {
		id = other.id;
		stationList = other.stationList;
		planList = other.planList;
		for (int i = 1; i <= 3; ++i)
			seat[i] = other.seat[i];
		num = other.num;
		return *this;
	}
	string getId() const {return id;}
	string getSeat(int type) const {return seat[type];}
	vector<station> &getStationList() {return stationList;}
	station & getStation(const string &stationName) {
		if (num.find(stationName) == num.end()) throw index_out_of_bound();
		return station(num[stationName]);
	}
	station & getStation(const int &index) {
		if(index >= stationList.size()) throw index_out_of_bound();
		return stationList[index];
	}
	int getStationId(const string &stationName) {return num[stationName];}
	map<string, plan> &getPlanList() {return planList;}
	plan & getPlan(const string &startTime) {
		if(planList.find(startTime) == planList.end()) throw no_such_plan();
		return planList[startTime];
	}
	void pushStation(const station &st) {
		if(st.getStopTime() > st.getDepartTime()) throw invalid_station();
		for(int type = 1; type <= 2; ++type)
			if(st.getPrice(type) > st.getPrice(type + 1)) throw invalid_station();
		if(!stationList.empty()) {
			station &tmp = stationList.back();
			if(tmp.getDepartTime() > st.getStopTime()) throw invalid_station();
			if(tmp.getLength() > st.getLength()) throw invalid_station();
			for(int type = 1; type <= 3; ++type)
				if(tmp.getPrice(type) > st.getPrice(type)) throw invalid_station();
		}
		num[st.getName()] = stationList.size()
		stationList.push_back(st);
	}
	void popStation() {
		if(stationList.empty()) throw no_such_station();
		map<string,int> ::itearator it;
		it = num.find(stationList.back());num.erase(it);
		stationList.pop_back();
	}
	void insertPlan(const plan &pl) {
		const string &startTime = pl.getStartTime();
		if(planList.find(startTime) != planList.end()) throw existed_plan();
		planList.insert(std::make_pair(startTime, pl));
	}
	void deletePlan(const string &startTime) {
		if(planList.find(startTime) == planList.end()) throw no_such_plan();
		planList.erase(startTime);
	}
	
	friend std::ifstream operator>>(std::ifstream &file, train &tr) {
		file >> tr.id;
		for(int i = 1; i <= 3; ++i) file >> tr.seat[i];
		file >> stationList;
		file >> planList;
		file >> num;
		return file;
	}
	friend std::ofstream operator<<(std::ofstream &file, train &tr) {
		file << tr.id;
		for(int i = 1; i <= 3; ++i) file << tr.seat[i];
		file << stationList;
		file << planList;
		file << num;
		return file;
	}
};

}
#endif
