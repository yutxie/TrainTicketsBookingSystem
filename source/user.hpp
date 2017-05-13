//
//  user.hpp
//  user
//
//  Created by 李江贝 on 2017/4/18.
//  Copyright © 2017年 李江贝. All rights reserved.
//

#ifndef SJTU_USER_HPP
#define SJTU_USER_HPP
#include "list.hpp"
#include "ticket.hpp"
#include "string.hpp"
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
        
        string userId;
        string userName;
        string password;
        sjtu::list<sjtu::ticket> ticketList;
        
    public:
        
        user(){};
        
        user(const string _id, const string &_name, const string &_password = "000000"): userId(_id), userName(_name), password(_password){};
        
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
        
        const string & getId()const {
            return userId;
        }
        
        const string & getName()const {
            return userName;
        }
        
        const string & getPassword()const {
            return password;
        }
        
        list<ticket> &getTicketList() {
            return ticketList;
        }
        
        const ticket & getTicket(const string &ticketId)const {
            sjtu::list<ticket>::const_iterator it = ticketList.cbegin();
            for(int i = 0; i < ticketList.size(); ++i) {
                if(ticketId == (*it).getId()) {
                    return (*it);
                }
                ++it;
            }
            throw no_such_ticket();
        }
        
        void modifyName(const string &newName) {
            userName = newName;
            return;
        }
        
        void modifyPassword(string _password) {
            password = _password;
            return;
        }
        
        void orderTicket(const ticket &tk) {
            sjtu::list<ticket>::const_iterator it = ticketList.cbegin();
            for(int i = 0; i < ticketList.size(); ++i) {
                if(tk.getId() == (*it).getId()) {
                    throw existed_ticket();
                    return;
                }
                ++it;
            }
            ticketList.push_back(tk);
        }
        
        void disorderTicket(const string &ticketId) {
            sjtu::list<ticket>::iterator it = ticketList.begin();
            for(int i = 0; i < ticketList.size(); ++i) {
                if((*it).getId() == ticketId) {
                    ticketList.erase(it);
                    return;
                }
                ++it;
            }
            throw no_such_ticket();
            return;
        }
        
        friend std::ifstream &operator>>(std::ifstream &file, user &obj) {
			file >> obj.userId;
			file >> obj.userName;
			file >> obj.password;
			file >> obj.ticketList;
			return file;
        }
        
        friend std::ofstream &operator<<(std::ofstream &file, const user &obj) {
			file << obj.userId;
			file << obj.userName;
			file << obj.password;
			file << obj.ticketList;
			return file;
        }
    };
}


#endif /* user_hpp */
