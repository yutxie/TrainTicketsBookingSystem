//
//  vector.h
//  vector
//
//  Created by 李江贝 on 2017/4/6.
//  Copyright © 2017年 李江贝. All rights reserved.
//

#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include <iostream>
#include <climits>
#include <cstddef>
#include <fstream>
#include "exceptions.hpp"
#include "rwInt.hpp"

namespace sjtu {
	
    template<typename T>
    class vector {
    private:
        int maxlength;
        int length;
        T * data;
        void doublespace(){
        	T *p = data;
            maxlength = maxlength * 2;
            data = new T [maxlength];
            for (int i = 0; i < maxlength; ++i)
            	data[i] = p[i];
            delete p;
        }
    public:
        class const_iterator;
        class iterator {
        private:
            int index;
            T ** outer;
            iterator(T ** x,int pos = 0):index(pos),outer(x){}
            friend iterator vector::begin();
            friend iterator vector::end();
            friend iterator vector::insert(iterator pos, const T &value);
            friend iterator vector::erase(iterator pos);
        public:
            iterator(){};
            iterator operator+(const int &n) const {
                iterator tmp(outer, index + n);
                return tmp;
            }
            iterator operator-(const int &n) const {
                iterator tmp(outer, index - n);
                return tmp;
            }
            int operator-(const iterator &rhs) const {
                if(*outer != *(rhs.outer)) throw invalid_iterator();
                int tmp;
                tmp = index - rhs.index;
                return tmp;
            }
            iterator operator+=(const int &n) {
                index += n;
                return *this;
            }
            iterator operator-=(const int &n) {
                index -= n;
                return *this;
            }
            iterator operator++(int) {
                iterator tmp(outer, index);
                ++index;
                return tmp;
            }
            iterator& operator++() {
                ++index;
                return *this;
            }
            iterator operator--(int) {
                iterator tmp(outer, index);
                --index;
                return tmp;
            }
            iterator& operator--() {
                --index;
                return *this;
            }
            T& operator*() const{
                return (*outer)[index];
            }
            bool operator==(const iterator &rhs) const {
                if(*outer != *(rhs.outer) || index != rhs.index) return false;
                else{
                    return true;
                }
            }
            bool operator==(const const_iterator &rhs) const {
                if(*outer != *(rhs.outer) || index != rhs.index) return false;
                else{
                    return true;
                }
            }
            bool operator!=(const iterator &rhs) const {
                return !(*this == rhs);
            }
            bool operator!=(const const_iterator &rhs) const {
                return !(*this == rhs);
            }
        };
        class const_iterator {
        private:
            int index;
            T ** outer;
            const_iterator (T ** x ,int pos = 0):index(pos),outer(x){
            };
            friend const_iterator vector::cbegin()const;
            friend const_iterator vector::cend()const;
        public:
            const_iterator(){};
            const_iterator operator+(const int &n) const {
                const_iterator tmp(outer, index + n);
                return tmp;
            }
            const_iterator operator-(const int &n) const {
                const_iterator tmp(outer, index - n);
                return tmp;
            }
            int operator-(const const_iterator &rhs) const {
                if(*outer != *(rhs.outer)) throw invalid_iterator();
                int tmp;
                tmp = index - rhs.index;
                return tmp;
            }
            const_iterator operator+=(const int &n) {
                index += n;
                return *this;
            }
            const_iterator operator-=(const int &n) {
                index -= n;
                return * this;
            }
            const_iterator operator++(int) {
                const_iterator tmp(outer, index);
                ++index;
                return tmp;
            }
            const_iterator& operator++() {
                ++index;
                return *this;
            }
            const_iterator operator--(int) {
                iterator tmp(outer, index);
                --index;
                return tmp;
            }
            const_iterator& operator--() {
                --index;
                return *this;
            }

            T& operator*() const{
                return (*outer)[index];
            }
            bool operator==(const iterator &rhs) const {
                if(*outer != *(rhs.outer) || index != rhs.index) return false;
                else{
                    return true;
                }
            }
            bool operator==(const const_iterator &rhs) const {
                if(*outer != *(rhs.outer) || index != rhs.index) return false;
                else{
                    return true;
                }
            }
            bool operator!=(const iterator &rhs) const {
                return !(*this == rhs);
            }
            bool operator!=(const const_iterator &rhs) const {
                return !(*this == rhs);
            }

        };
        vector(int t = 10) {
            maxlength = t;
            length = 0;
            data = new T [t];
        }
        vector(const vector &other) {
            maxlength = 2 * other.size();
            length = other.length;
            data = new T [maxlength];
            for (int i = 0; i < other.length; ++i)
            	data[i] = other.data[i];
        }
        ~vector() {delete [] data;}
        vector &operator=(const vector &other) {
            if(this == &other) return *this;
            maxlength = 2 * other.size();
            length = other.length;
            delete [] data;
            data = new T [maxlength];
            for (int i = 0; i < other.length; ++i)
            	data[i] = other.data[i];
            return *this;
        }
        T & at(const size_t &pos) {
            if(pos >= size() || pos < 0) throw index_out_of_bound();
            return data[pos];
        }
        const T & at(const size_t &pos) const {
            if(pos >= size() || pos < 0) throw index_out_of_bound();
            return data[pos];
        }
        T & operator[](const size_t &pos) {
            if(pos >= size() || pos < 0) throw index_out_of_bound();
            return data[pos];
        }
        const T & operator[](const size_t &pos) const {
            if(pos >= size() || pos < 0) throw index_out_of_bound();
            return data[pos];
        }
        const T & front() const {
            if(size() == 0) throw container_is_empty();
            return data[0];
        }
        const T & back() const {
            if(size() == 0) throw container_is_empty();
            return data[length - 1];
        }
        iterator begin() {
            iterator tmp(&data, 0);
            return tmp;
        }
        const_iterator cbegin() const {
            const_iterator tmp2((T**)&data, 0);
            return tmp2;
        }
        iterator end() {
            iterator tmp(&data, length);
            return tmp;
        }
        const_iterator cend() const {
            const_iterator tmp2((T**)&data, length);
            return tmp2;
        }
        bool empty() const {
            if(length == 0){
                return true;
            }
            else{
                return false;
            }
        }
        size_t size() const {
            return length;
        }
        size_t capacity() const {
            return maxlength;
        }
        void clear() {
            length = 0;
        }
        iterator insert(iterator pos, const T &value) {
            if(maxlength == length) doublespace();
            ++length;
            int tmp = pos.index;
            for(int i = length - 1; i > tmp; --i){
                data[i] = data[i - 1];
            }
            data[tmp] = value;
            return pos;
        }
        iterator insert(const size_t &ind, const T &value) {
            if(ind > size() || ind < 0)throw index_out_of_bound();
            if(length == maxlength)doublespace();
            ++length;
            for(int i = length - 1; i > ind; --i){
                data[i] = data[i - 1];
            }
            data[ind] = value;
            iterator tmp((begin().outer), ind);
            return tmp;
        }
        iterator erase(iterator pos) {
            if(pos.index == length - 1) {
                --length;
                iterator tmp ((pos.outer), length - 1);
                return tmp;
            }
            --length;
            for(int i = pos.index; i < length; ++i){
                data[i] = data[i + 1];
            }
            return pos;
        }
        iterator erase(const size_t &ind) {
            if(ind >= length || ind < 0) throw index_out_of_bound();
            if(ind == length - 1){
                --length;
                iterator tmp((begin().outer), length - 1);
                return tmp;
            }
            for(int i = ind; i < length - 1; ++i){
                data[i] = data[i + 1];
            }
            --length;
            iterator tmp((begin().outer), ind);
            return tmp;
        }
        void push_back(const T &value) {
            if(length == maxlength) doublespace();
            data[length++] = value;
        }
        void pop_back() {
            if(length == 0) throw container_is_empty();
            --length;
        }
		friend std::ifstream &operator>>(std::ifstream &file, vector &obj) {
			if(!obj.empty()) throw container_is_not_empty();
			obj.clear();
			int n = 0;
			file >> n;
			std::cout << n << std::endl;
			for(int i = 0; i < n; ++i) {
				T x;
				file >> x;
				std::cout << x << std::endl;
				obj.push_back(x);
			}
			return file;
		}
		friend std::ofstream &operator<<(std::ofstream &file, const vector &obj) {
			file << obj.length;
			for (int i = 0; i < obj.length; ++i) {
				file << obj.data[i];
			}
			return file;
		}
    };
}

#endif
