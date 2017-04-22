#ifndef SJTU_TRAIN_HPP
#define SJTU_TRAIN_HPP

#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <fstream>
#include "station.hpp"
#include "exceptions.hpp"
#include "plan_dev.hpp"

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
	std::vector<station> stationList;
	std::map<timer, plan> planList;
public:
	train() {}
	train(const std::string &_id) : id(_id) {}
	train(const train &other) {
		id = other.id;
		stationList = other.stationList;
		planList = other.planList;
	}
	train & operator=(const train &other) {
		id = other.id;
		stationList = other.stationList;
		planList = other.planList;
		return *this;
	}
	void getStationList(std::ostream &os) const {
		int sz = stationList.size();
		if(sz < 2) os << "There is " << sz << "station\n";
		else os << "There are " << sz << "stations\n";
		for(int i = 0; i < sz; ++i) {
			os << "Station No." << i << "\n";
			os << stationList[i];
		}
	}
	station & getStation(int index) {
		if(index >= stationList.size()) throw index_out_of_bound();
		return stationList[index];
	}
	void getPlanList(std::ostream &os) {
		int sz = planList.size();
		if(sz < 2) os << "There is " << sz << "plan\n";
		else os << "There are " << sz << "plans\n";
		int cnt = 1;
		for(std::map<timer, plan>::iterator it = planList.begin(); it != planList.end(); ++it, ++cnt) {
			os << "Plan No." << cnt << "\n";
			os << it -> second;
		}
	}
	plan & getPlan(const timer &startTime) {
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
		stationList.push_back(st);
	}
	void popStation() {
		if(stationList.empty()) throw no_such_station();
		stationList.pop_back();
	}
	void insertPlan(const plan &pl) {
		const timer &startTime = pl.getStartTime();
		if(planList.find(startTime) != planList.end()) throw existed_plan();
		planList.insert(std::make_pair(startTime, pl));
	}
	void deletePlan(const timer &startTime) {
		if(planList.find(startTime) == planList.end()) throw no_such_plan();
		planList.erase(startTime);
	}
	friend std::ostream & operator<<(std::ostream &os, train &obj) {
		os << "Train id: " << obj.id << "\n";
		obj.getStationList(os);
		obj.getPlanList(os);
		return os;
	}
	void readIn(std::ifstream &file) {
		int idLength;
		file.read(reinterpret_cast<char *> (&idLength), sizeof(int));
		id = "";
		for(int i = 0; i < idLength; ++i) {
			char ch;
			file.read(reinterpret_cast<char *> (&ch), sizeof(char));
			id += ch;
		}
		// stationList.readIn(file);
		// planList.readIn(file);
	}
	void writeOut(std::ofstream &file) const {
		int idLength = id.length();
		file.write(reinterpret_cast<const char *> (&idLength), sizeof(int));
		for(int i = 0; i < idLength; ++i) {
			char ch = id[i];
			file.write(reinterpret_cast<const char *> (&ch), sizeof(char));
		}
		// stationList.writeOut(file);
		// planList.writeOut(file);
	}
};

}
#endif