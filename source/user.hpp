//
//  user.hpp
//  user
//
//  Created by 李江贝 on 2017/4/18.
//  Copyright © 2017年 李江贝. All rights reserved.
//

#ifndef SJTU_USER_HPP
#define SJTU_USER_HPP

#include "rwFile.hpp"
#include "list.hpp"
#include "ticket.hpp"
#include "exceptions.hpp"

namespace sjtu {
    class user {
    private:
        class existed_ticket : public exception {
        public:
            existed_ticket() : exception(
                "existed_ticket",
                "Existed ticket"
            ) {}
        };
        
        class no_such_ticket : public exception {
        public:
            no_such_ticket() : exception(
                "no_such_ticket",
                "No such ticket"
            ) {}
        };
    
        std::string userId;
        std::string userName;
        std::string password;
        sjtu::list<sjtu::ticket> ticketList;
        
    public:
        
        user(){};
        
        user(const std::string _id, const std::string &_name, const std::string &_password = "000000"): userId(_id), userName(_name), password(_password){};
        
        user(const user &other) {
            userId = other.userId;
            userName = other.userName;
            password = other.password;
        }
        
        user &operator=(const user &other) {
            userId = other.userId;
            userName = other.userName;
            password = other.password;
            return *this;
        }
        
        const std::string & getId()const {
            return userId;
        }
        
        const std::string & getName()const {
            return userName;
        }
        
        const std::string & getPassword()const {
            return password;
        }
        
        list<ticket> &getTicketList() {
            return ticketList;
        }
        
        const ticket & getTicket(const std::string &ticketId)const {
            sjtu::list<ticket>::const_iterator it = ticketList.cbegin();
            for(size_t i = 0; i < ticketList.size(); ++i) {
                if(ticketId == (*it).getId()) {
                    return (*it);
                }
                ++it;
            }
            throw no_such_ticket();
        }
        
        void modifyName(const std::string &newName) {
            userName = newName;
            return;
        }
        
        void modifyPassword(std::string _password) {
            password = _password;
            return;
        }
        
        void orderTicket(const ticket &tk) {
            sjtu::list<ticket>::const_iterator it = ticketList.cbegin();
            for(size_t i = 0; i < ticketList.size(); ++i) {
                if(tk.getId() == (*it).getId()) {
                    throw existed_ticket();
                    return;
                }
                ++it;
            }
            ticketList.push_back(tk);
        }
        
        void disorderTicket(const std::string &ticketId, int dlt) {
            sjtu::list<ticket>::iterator it = ticketList.begin();
            for(size_t i = 0; i < ticketList.size(); ++i) {
                if((*it).getId() == ticketId) {
					int number = (*it).getNumber();
					if(number < dlt) throw invalid_input();
					number -= dlt;
					(*it).modifyNumber(number);
                    if(number == 0)ticketList.erase(it);
                    return;
                }
                ++it;
            }
            throw no_such_ticket();
            return;
        }
        
        friend void readIn(std::ifstream &file, user &obj) {
			readIn(file, obj.userId);
			readIn(file, obj.userName);
			readIn(file, obj.password);
			readIn(file, obj.ticketList);
        }
        
        friend void writeOut(std::ofstream &file, const user &obj) {
			writeOut(file, obj.userId);
			writeOut(file, obj.userName);
			writeOut(file, obj.password);
			writeOut(file, obj.ticketList);
        }
    };
}


#endif /* user_hpp */
