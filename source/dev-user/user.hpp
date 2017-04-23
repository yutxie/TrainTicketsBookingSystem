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
#include "exception.hpp"
namespace sjtu {
    class user {
        class already_ordered : public exception {
        public:
            already_ordered() : exception(
                "already_ordered",
                "Already ordered"
            ) {}
        };
        class not_ordered : public exception {
        public:
            not_ordered() : exception(
                                      "not_ordered",
                                      "Not ordered"
                                      ) {}
        };
    private:
        std::string userId;
        std::string userName;
        std::string password;
        int identity;
        sjtu::list <sjtu::ticket> ticketList;
    public:
        user(){};
        
        user(const std::string _id, const std::string &_name, const std::string &_password = "000000"): userId(_id), userName(_name), password(_password)){};
        
        user(const user &other) {
            userId = other.userId;
            userName = other.userName;
            password = other.password;
        }
        
        user &operator=(const user &other) {
            userId = other.userId;
            userName = other.userName;
            password = other.password;
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
            for(int i = 0; i < ticketList.size(); ++i) {
                os << "ticketList: " << ticketList[i].getId() << " ";
            }
            os << std::endl;
        }
        
        //较难实现
        const ticket & getTicket(const std::string &ticketId)const {
            for()
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
            ticketList.push_back
        }
        friend std::ostream& operator <<(std::ostream &os, const user &obj) {
            os << "userId: " << obj.userId << std::endl;
            os << "userName: " << obj.userName << std::endl;
            os << "password: " << obj.password << std::endl;
            os << "identity: " << obj.identity << std::endl;
            os << "bookedTicket: ";
            for(int i = 0; i < obj.bookedTicket.size(); ++i) {
                os << obj.bookedTicket[i] << std::endl;
            }
            return os;
        }
        bookInquiry
    };
}


#endif /* user_hpp */
