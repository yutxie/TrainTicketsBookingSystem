#ifndef SJTU_TRAIN_HPP
#define SJTU_TRAIN_HPP

#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include "rwFile.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "station.hpp"
#include "exceptions.hpp"
#include "plan.hpp"

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
	std::string id;
	vector<station> stationList;
	map<std::string, plan> planList;
	map<std::string,int> num;
public:
	train() {}
	train(const std::string &_id) : id(_id) {}
	train(const train &other) :id(other.id),stationList(other.stationList),planList(other.planList),num(other.num) {}
	train & operator=(const train &other) {
		id = other.id;
		stationList = other.stationList;
		planList = other.planList;
		num = other.num;
		return *this;
	}
	const std::string getId() const {return id;}
	vector<station> &getStationList() {return stationList;}
	const vector<station> &getStationList() const {return stationList;}
	station & getStation(const std::string &stationName) {
		if (num.find(stationName) == num.end()) throw index_out_of_bound();
		return stationList[num[stationName]];
	}
	const station & getStation(const std::string &stationName) const {
		if (num.find(stationName) == num.cend()) throw index_out_of_bound();
		return stationList[num[stationName]];
	}
	station & getStation(const int &index) {
		if(index >= int(stationList.size())) throw index_out_of_bound();
		return stationList[index];
	}
	const station & getStation(const int &index) const {
		if(index >= int(stationList.size())) throw index_out_of_bound();
		return stationList[index];
	}
	int getStationId(const std::string &stationName) {return num[stationName];}
	map<std::string, plan> &getPlanList() {return planList;}
	plan & getPlan(const std::string &startTime) {
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
		num[st.getName()] = stationList.size();
		stationList.push_back(st);
	}
	void popStation() {
		if(stationList.empty()) throw no_such_station();
		map<std::string,int>::iterator it;
		it = num.find(stationList.back().getName());num.erase(it);
		stationList.pop_back();
	}
	void insertPlan(const plan &pl) {
		const std::string &startDate = pl.getStartDate();
		if(planList.find(startDate) != planList.end()) throw existed_plan();
		planList.insert(std::make_pair(startDate, pl));
	}
	void deletePlan(const std::string &startTime) {
		auto it = planList.find(startTime);
		if(it == planList.end()) throw no_such_plan();
		planList.erase(it);
	}
	
	friend void readIn(std::ifstream &file, train &tr) {
		readIn(file, tr.id);
		readIn(file, tr.stationList);
		readIn(file, tr.planList);
		readIn(file, tr.num);
	}
	friend void writeOut(std::ofstream &file, const train &tr) {
		writeOut(file, tr.id);
		writeOut(file, tr.stationList);
		writeOut(file, tr.planList);
		writeOut(file, tr.num);
	}
};

}
#endif
