//车票管理类系统 
#ifndef SJTU_TICKET_HPP
#define SJTU_TICKET_HPP

#include <string>
#include <fstream>
#include "rwFile.hpp"
#include "exceptions.hpp"

namespace sjtu{
	class ticket{
	private:
		std::string id;
		std::string trainId;//所属车次
		std::string userId;//用户ID
		std::string userName;//用户名 
		std::string departStation;//起点站 
		std::string stopStation;//终点站 
		std::string startDate;
		std::string departTime;//出发时间 
		std::string stopTime;//到达时间 
		int seatType;//座位类型 
		double price;//票价 
		int number;
		
	public:
		ticket() {}
		ticket(const std::string &_id, const std::string &_train, const std::string &_userId, 
			const std::string &_userName, const std::string &_departStation,
			const std::string &_stopStation, const std::string &_startDate, const std::string &_departTime, 
			const std::string &_stopTime, int _seatType, double _price, int _number): id(_id), 
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
		
		const std::string & getId() const {
			return id;
		}
		
		const std::string & getTrain() const {
			return trainId;
		}
		
		const std::string & getUserId() const{
			return userId; 
		}
		
		const std::string & getUserName() const{
			return userName;
		}
		
		const std::string & getDepartStation() const{
			return departStation;
		}
		
		const std::string & getStopStation() const{
			return stopStation;
		}
		
		const std::string & getStartDate() const {
			return startDate;
		}
		
		const std::string & getDepartTime() const {
			return departTime;
		}
		
		const std::string & getStopTime() const {
			return stopTime;
		}
		
		int getType() const{
			return seatType;
		}
		
		double getPrice() const {
			return price;
		}
		
		int getNumber() const {
			return number;
		}
		
		void modifyNumber(int _number) {
			if(_number < 0) throw invalid_input();
			number = _number;
		}
		
		friend void readIn(std::ifstream &file, ticket &tk) {
			readIn(file, tk.id);
			readIn(file, tk.trainId);
			readIn(file, tk.userId);
			readIn(file, tk.userName);
			readIn(file, tk.departStation);
			readIn(file, tk.stopStation);
			readIn(file, tk.startDate);
			readIn(file, tk.departTime);
			readIn(file, tk.stopTime);
			readIn(file, tk.seatType);
			readIn(file, tk.price);
			readIn(file, tk.number);
		}
		friend void writeOut(std::ofstream &file, const ticket &tk) {
			writeOut(file, tk.id);
			writeOut(file, tk.trainId);
			writeOut(file, tk.userId);
			writeOut(file, tk.userName);
			writeOut(file, tk.departStation);
			writeOut(file, tk.stopStation);
			writeOut(file, tk.startDate);
			writeOut(file, tk.departTime);
			writeOut(file, tk.stopTime);
			writeOut(file, tk.seatType);
			writeOut(file, tk.price);
			writeOut(file, tk.number);
		}
	};

}
#endif/*station_hpp*/
