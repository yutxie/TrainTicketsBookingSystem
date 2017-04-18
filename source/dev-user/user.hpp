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
namespace sjtu {
    class user {
    private:
        int userId;
        std::string userName;
        int password;
        int identity;
        sjtu::list <sjtu::ticket> bookedTicket;
    public:
        user(){};
        
        user(int _id, const std::string &_name, int _password, int _identity, const sjtu::list <sjtu::ticket> &_book): userId(_id), userName(_name), password(_password), identity(_identity), bookedTicket(_book){}
        
        user(const user &other) {
            userId = other.userId;
            userName = other.userName;
            password = other.password;
            identity = other.identity;
            bookedTicket = other.bookedTicket;
        }
        
        user &operator=(const user &other) {
            userId = other.userId;
            userName = other.userName;
            password = other.password;
            identity = other.identity;
            bookedTicket = other.bookedTicket;
        }
        
        void modifyUserName(const std::string &_name) {
            userName = _name;
            return;
        }
        
        void modifyPassword(int _password) {
            password = _password;
            return;
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
