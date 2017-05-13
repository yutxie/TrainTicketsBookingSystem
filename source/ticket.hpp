//车票管理类系统 
#ifndef SJTU_TICKET_HPP
#define SJTU_TICKET_HPP

#include <string>
#include <fstream>
#include "exceptions.hpp"
#include "string.hpp"

namespace sjtu{
	class ticket{
	private:
		string id;
		string trainId;//所属车次
		string userId;//用户ID
		string userName;//用户名 
		string departStation;//起点站 
		string stopStation;//终点站 
		string startDate;
		string departTime;//出发时间 
		string stopTime;//到达时间 
		int seatType;//座位类型 
		int price;//票价 
		int number;
		
	public:
		ticket() {}
		ticket(const string &_id, const string &_train, const string &_userId, 
			const string &_userName, const string &_departStation,
			const string &_stopStation, const string &_startDate, const string &_departTime, 
			const string &_stopTime, int _seatType, int _price, int _number): id(_id), 
			trainId(_train), userId(_userId), userName(_userName), 
			departStation(_departStation), stopStation(_stopStation), 
			startDate(_startDate), departTime(_departTime), stopTime(_stopTime), 
			seatType(_seatType),price(_price), number(_number) {}
		
		ticket(const ticket &other){
			id = other.id;
			trainId=other.trainId;
			userId=other.userId;
			userName=other.userName;
			departStation=other.departStation;
			stopStation=other.stopStation;
			startDate = other.startDate;
			departTime=other.departTime;
			stopTime=other.stopTime;
			seatType=other.seatType;
			price=other.price;
			number = other.number;
		}
		
		ticket &operator=(const ticket &other){
			id = other.id;
			trainId=other.trainId;
			userId=other.userId;
			userName=other.userName;
			departStation=other.departStation;
			stopStation=other.stopStation;
			startDate = other.startDate;
			departTime=other.departTime;
			stopTime=other.stopTime;
			seatType=other.seatType;
			price=other.price;
			number = other.number;
			return *this;
		}
		
		const string & getId() const {
			return id;
		}
		
		const string & getTrain() const {
			return trainId;
		}
		
		const string & getUserId() const{
			return userId; 
		}
		
		const string & getUserName() const{
			return userName;
		}
		
		const string & getDepartStation() const{
			return departStation;
		}
		
		const string & getStopStation() const{
			return stopStation;
		}
		
		const string & getStartDate() const {
			return startDate;
		}
		
		const string & getDepartTime() const {
			return departTime;
		}
		
		const string & getStopTime() const {
			return stopTime;
		}
		
		int getType() const{
			return seatType;
		}
		
		int getPrice() const {
			return price;
		}
		
		int getNumber() const {
			return number;
		}
		
		friend std::ifstream &operator>>(std::ifstream &file, ticket &tk) {
			file >> tk.id;
			file >> tk.trainId;
			file >> tk.userId;
			file >> tk.userName;
			file >> tk.departStation;
			file >> tk.stopStation;
			file >> tk.startDate;
			file >> tk.departTime;
			file >> tk.stopTime;
			file.read(reinterpret_cast<char *> (&tk.seatType), sizeof(int));
			file.read(reinterpret_cast<char *> (&tk.price), sizeof(int));
			file.read(reinterpret_cast<char *> (&tk.number), sizeof(int));
			return file;
		}
		friend std::ofstream &operator<<(std::ofstream &file, const ticket &tk) {
			file << tk.id;
			file << tk.trainId;
			file << tk.userId;
			file << tk.userName;
			file << tk.departStation;
			file << tk.stopStation;
			file << tk.startDate;
			file << tk.departTime;
			file << tk.stopTime;
			file.write(reinterpret_cast<const char *> (&tk.seatType), sizeof(int));
			file.write(reinterpret_cast<const char *> (&tk.price), sizeof(int));
			file.write(reinterpret_cast<const char *> (&tk.number), sizeof(int));
			return file;
		}
	};

}
#endif/*station_hpp*/
