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
#include "exceptions.hpp"
#include "rwString.hpp"
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
        int identity;
        sjtu::list <sjtu::ticket> ticketList;
        
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
        
        void getTicketList(std::ostream &os) const {
            sjtu::list<ticket>::const_iterator it = ticketList.cbegin();
            for(int i = 0; i < ticketList.size(); ++i) {
                os << (*it).getId() << std::endl;
                ++it;
            }
            os << std::endl;
        }
        
        const ticket & getTicket(const std::string &ticketId)const {
            sjtu::list<ticket>::const_iterator it = ticketList.cbegin();
            for(int i = 0; i < ticketList.size(); ++i) {
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
        
        void modifyPassword(int _password) {
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
        
        void disorderTicket(const std::string &ticketId) {
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
        
        friend std::ostream& operator <<(std::ostream &os, const user &obj) {
            os << "userId: " << obj.userId << std::endl;
            os << "userName: " << obj.userName << std::endl;
            os << "password: " << obj.password << std::endl;
            os << "ticketList: ";
            sjtu::list<ticket>::const_iterator it = obj.ticketList.cbegin();
            for(int i = 0; i < obj.ticketList.size(); ++i) {
                os << (*it) << std::endl;
                ++it;
            }
            return os;
        }
        
        void readIn(std::ifstream &file) {
            readString(file, userId);
            readString(file, userName);
            readString(file, password);
            ticketList.readIn(file);
        }
        
        void writeOut(std::ofstream &file) {
            writeString(file, userId);
            writeString(file, userName);
            writeString(file, password);
            ticketList.writeOut(file);
        }
    };
}


#endif /* user_hpp */
