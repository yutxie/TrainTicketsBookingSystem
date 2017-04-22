//
//  station.hpp
//  station
//
//  Created by 李江贝 on 2017/4/13.
//  Copyright © 2017年 李江贝. All rights reserved.
//

#ifndef SJTU_STATION_HPP
#define SJTU_STATION_HPP
#include "exceptions.hpp"
#include "timer.hpp"
#include <iostream>
namespace sjtu {
    class station {
    private:
        std::string stationName;
        int stationId;
        std::string trainName;
        sjtu::timer stopTime;
        sjtu::timer departTime;
        int lengthFromStart;
        int price[4];
        
    public:
        station() {};
        
        station(const std::string &_name, int _id, const std::string &_train, const sjtu::timer &_stopTime, const sjtu::timer &_departTime, int _length, int _price[]) : stationName(_name), stationId(_id), trainName(_train), stopTime(_stopTime), departTime(_departTime), lengthFromStart(_length) {
            for(int i = 1; i <= 3; ++i) {
                price[i] = _price[i];
            }
        };
        
        station(const station &other) {
            stationName = other.stationName;
            stationId = other.stationId;
            trainName = other.trainName;
            stopTime = other.stopTime;
            departTime = other.departTime;
            lengthFromStart = other.lengthFromStart;
            for(int i = 1; i <= 3; ++i) {
                price[i] = other.price[i];
            }
        }
        
        station &operator=(const station & other) {
            stationName = other.stationName;
            stationId = other.stationId;
            trainName = other.trainName;
            stopTime = other.stopTime;
            departTime = other.departTime;
            lengthFromStart = other.lengthFromStart;
            for(int i = 1; i <= 3; ++i) {
                price[i] = other.price[i];
            }
            return *this;
        }
        
        const std::string & getName() const {
            return stationName;
        }
        
        int getId() const {
            return stationId;
        }
        
        const std::string & getTrain() const {
            return trainName;
        }
        
        int getLength() const {
            return lengthFromStart;
        }
        
        int getPrice(int type) const {
            return price[type];
        }
        
        const sjtu::timer & getStopTime() const {
            return stopTime;
        }
        
        const sjtu::timer & getDepartTime() const {
            return departTime;
        }
        
        void modifyPrice(int type, int newPrice) {
            price[type] = newPrice;
            return;
        }
        
        friend std::ostream& operator <<(std::ostream &os, const station &obj) {
            os << "stationName: " << obj.stationName << std::endl;
            os << "stationId: " << obj.stationId << std::endl;
            os << "trainName: " << obj.trainName << std::endl;
            os << "stopTime: " << obj.stopTime << std::endl;
            os << "departTime: " << obj.departTime << std::endl;
            os << "lengthFromStart: " << obj.lengthFromStart << std::endl;
            os << "price: " << obj.price[1] << " " << obj.price[2] << " " << obj.price[3] << std::endl;
            return os;
        }
    };
}


#endif /* station_hpp */