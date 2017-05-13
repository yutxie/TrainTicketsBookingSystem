//
//  station.hpp
//  station
//
//  Created by 李江贝 on 2017/4/13.
//  Copyright © 2017年 李江贝. All rights reserved.
//

#ifndef SJTU_STATION_HPP
#define SJTU_STATION_HPP

#include <fstream>
#include <iostream>
#include <string>
#include "rwFile.hpp"
#include "exceptions.hpp"

namespace sjtu {
    class station {
    private:
        std::string stationName;
        std::string trainName;
        std::string stopTime;
        std::string departTime;
        int lengthFromStart;
        double price[4];
        
    public:
        station() {};
        
        station(const std::string &_name, const std::string &_train, const std::string &_stopTime, const std::string &_departTime, int _length, double _price[]) : stationName(_name), trainName(_train), stopTime(_stopTime), departTime(_departTime), lengthFromStart(_length) {
            for(int i = 1; i <= 3; ++i) {
                price[i] = _price[i];
            }
        };
        
        station(const station &other) {
            stationName = other.stationName;
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
        
        const std::string & getTrain() const {
            return trainName;
        }
        
        int getLength() const {
            return lengthFromStart;
        }
        
        double getPrice(int type) const {
            return price[type];
        }
        
        const std::string & getStopTime() const {
            return stopTime;
        }
        
        const std::string & getDepartTime() const {
            return departTime;
        }
        
        void modifyPrice(int type, double newPrice) {
            price[type] = newPrice;
            return;
        }
		
		// read in & write out by xxxxxyt
		
		friend void readIn(std::ifstream &file, station &st) {
			readIn(file, st.stationName);
			readIn(file, st.trainName);
			readIn(file, st.stopTime);
			readIn(file, st.departTime);
			readIn(file, st.lengthFromStart);
			for(int i = 1; i <= 3; ++i)
				readIn(file, st.price[i]);
		}
		friend void writeOut(std::ofstream &file, const station &st) {
			writeOut(file, st.stationName);
			writeOut(file, st.trainName);
			writeOut(file, st.stopTime);
			writeOut(file, st.departTime);
			writeOut(file, st.lengthFromStart);
			for(int i = 1; i <= 3; ++i)
				writeOut(file, st.price[i]);
		}
    };
}


#endif /* station_hpp */
