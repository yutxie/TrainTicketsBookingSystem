//
//  station.hpp
//  station
//
//  Created by 李江贝 on 2017/4/13.
//  Copyright © 2017年 李江贝. All rights reserved.
//

#ifndef SJTU_STATION_HPP
#define SJTU_STATION_HPP
#include <exceptions.hpp>
#include <timer.hpp>
namespace sjtu {
    class station {
    private:
        string stationName;
        string trainName;
        int stationId;
        int lengthFromStart;
        int price[4];
        timer stopTime;
        timer departTime;
    public:
        station(const string &_name, int _id, const string &_train, const timer &_stopTime, const timer &_departTime, int _length, int _price[]) : stationName(_name), stationId(_id), trainName(_train), stopTime(_stopTime), departTime(_departTime), lengthFromStart(_length) {
            for(int i = 1; i <= 3; ++i){
                price[i] = _price[i];
            }
        };
        
        string getName() const {
            return stationName;
        }
        
        int getId() const {
            return stationId;
        }
        
        string getTrain() const {
            return trainName;
        }
        
        int getLength() const {
            return lengthFromStart;
        }
        
        int getPrice(int type) const {
            return price[type];
        }
        
        timer getStopTime() const {
            return stopTime;
        }
        
        timer getDepartTime() const {
            return departTime;
        }
        
        void changePrice(int type, int currentPrice) {
            price[type] = currentPrice;
            return;
        }
    };
}


#endif /* station_hpp */
