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
#include "exceptions.hpp"
#include "string.hpp"
namespace sjtu {
    class station {
    private:
        string stationName;
        string trainName;
        string stopTime;
        string departTime;
        int lengthFromStart;
        int price[4];
        
    public:
        station() {};
        
        station(const string &_name, const string &_train, const string &_stopTime, const string &_departTime, int _length, int _price[]) : stationName(_name), trainName(_train), stopTime(_stopTime), departTime(_departTime), lengthFromStart(_length) {
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
        
        const string & getName() const {
            return stationName;
        }
        
        const string & getTrain() const {
            return trainName;
        }
        
        int getLength() const {
            return lengthFromStart;
        }
        
        int getPrice(int type) const {
            return price[type];
        }
        
        const string & getStopTime() const {
            return stopTime;
        }
        
        const string & getDepartTime() const {
            return departTime;
        }
        
        void modifyPrice(int type, int newPrice) {
            price[type] = newPrice;
            return;
        }
		
		// read in & write out by xxxxxyt
		
		friend std::ifstream &operator>>(std::ifstream &file, station &st) {
			file >> st.stationName;
			file >> st.trainName;
			file >> st.stopTime;
			file >> st.departTime;
			file.read(reinterpret_cast<char *> (&st.lengthFromStart), sizeof(int));
			for(int i = 1; i <= 3; ++i) {
				file.read(reinterpret_cast<char *> (&st.price[i]), sizeof(int));
			}
			return file;
		}
		friend std::ofstream &operator<<(std::ofstream &file, const station &st) {
			file << st.stationName;
			file << st.trainName;
			file << st.stopTime;
			file << st.departTime;
			file.write(reinterpret_cast<const char *> (&st.lengthFromStart), sizeof(int));
			for(int i = 1; i <= 3; ++i) {
				file.write(reinterpret_cast<const char *> (&st.price[i]), sizeof(int));
			}
			return file;
		}
    };
}


#endif /* station_hpp */
