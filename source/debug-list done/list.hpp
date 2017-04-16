//
//  list.h
//  list
//
//  Created by 李江贝 on 2017/4/6.
//  Copyright © 2017年 李江贝. All rights reserved.
//

#ifndef _SJTU_LIST_HPP
#define _SJTU_LIST_HPP
/**
 * similar to vector.hpp in STLite
 */
#include "exceptions.hpp"
#include <iostream>
#include <climits>
#include <cstddef>
#include <fstream>
#include <string>
namespace sjtu{
template<typename T>
class list {
private:
    struct node{
        T value;
        node * next;
        node * prev;
        node(){
            next = NULL;
            prev = NULL;
        };
        node(const T & x, node * i, node * j){
            value = x;
            next = i;
            prev = j;
        }
    };
    node * head;
    node * tail;
    int currentlength;
	std::fstream io;
public:
    /**
     * TODO
     * a type for actions of the elements of a list, and you should write
     *   a class named const_iterator with same interfaces.
     */
    /**
     * you can see RandomAccessIterator at CppReference for help.
     */
    class iterator {
    private:
        node * index;
        /**
         * TODO add data members
         *   just add whatever you want.
         */
        friend iterator list::begin();
        friend iterator list::end();
        friend iterator list::erase(iterator pos);
        friend iterator list::insert(iterator pos, const T &value);
        iterator(node * x): index(x){};
    public:
        /**
         * return a new iterator which pointer n-next elements
         *   even if there are not enough elements, just return the answer.
         * as well as operator-
         */
        iterator operator+(const int &n) const {
            iterator tmp(index);
            for(int i = 1 ; i <= n; ++i){
                tmp.index = tmp.index -> next;
                if(tmp.index -> next == NULL){
                    throw index_out_of_bound();
                    break;
                }
            }
            return tmp;
            //TODO
        }
        iterator operator-(const int &n) const {
            iterator tmp(index);
            for(int i = 1 ; i <= n; ++i){
                tmp.index = tmp.index -> prev;
                if(tmp.index -> prev == NULL){
                    throw index_out_of_bound();
                    break;
                }
            }
            return tmp;
            //TODO
        }
        // return th distance between two iterator,
        // if these two iterators points to different vectors, throw invaild_iterator.
        int operator-(const iterator &rhs) const {
            int num = 0;
            node * tmp = index;
            while(tmp -> prev -> prev != NULL){
                tmp = tmp -> prev;
                num++;
                if(tmp == rhs.index){
                    return num;
                }
            }
            tmp = index;
            num = 0;
            while(tmp -> next -> next != NULL){
                tmp = tmp -> next;
                num--;
                if(tmp == rhs.index){
                    return num;
                }
            }
            throw invalid_iterator();
            
            //TODO
        }
        iterator operator+=(const int &n) {
            for(int i = 1 ; i <= n; ++i){
                index = index -> next;
                if(index -> next == NULL){
                    throw index_out_of_bound();
                    break;
                }
            }
            return *this;
            //TODO
        }
        iterator operator-=(const int &n) {
            for(int i = 1 ; i <= n; ++i){
                index = index -> prev;
                if(index -> prev == NULL){
                    throw index_out_of_bound();
                    break;
                }
            }
            return *this;
            //TODO
        }
        /**
         * TODO iter++
         */
        iterator operator++(int) {
            iterator tmp(index);
            index = index -> next;
            if(index -> next == NULL) throw index_out_of_bound();
            return tmp;
        }
        /**
         * TODO ++iter
         */
        iterator& operator++() {
            index = index -> next;
            if(index -> next == NULL) throw index_out_of_bound();
            return * this;
        }
        /**
         * TODO iter--
         */
        iterator operator--(int) {
            iterator tmp(index);
            index = index -> prev;
            if(index -> prev == NULL) throw index_out_of_bound();
            return tmp;
        }
        /**
         * TODO --iter
         */
        iterator& operator--() {
            index = index -> prev;
            if(index -> prev == NULL) throw index_out_of_bound();
            return * this;
        }
        /**
         * TODO *it
         */
        T& operator*() const{
            return index -> value;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory).
         */
        bool operator==(const iterator &rhs) const {
            if(index == rhs -> index) return true;
            else{
                return false;
            }
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            if(index == rhs.index) return false;
            else{
                return true;
            }
        }
    };
    
    class const_iterator {
    private:
        node * index;
        /**
         * TODO add data members
         *   just add whatever you want.
         */
        friend const_iterator list::cbegin()const;
        friend const_iterator list::cend()const;
        const_iterator(node * x): index(x){};
    public:
        /**
         * return a new iterator which pointer n-next elements
         *   even if there are not enough elements, just return the answer.
         * as well as operator-
         */
        const_iterator operator+(const int &n) const {
            const_iterator tmp(index);
            for(int i = 1 ; i <= n; ++i){
                tmp.index = tmp.index -> next;
                if(tmp.index -> next == NULL){
                    throw index_out_of_bound();
                    break;
                }
            }
            return tmp;
            //TODO
        }
        const_iterator operator-(const int &n) const {
            const_iterator tmp(index);
            for(int i = 1 ; i <= n; ++i){
                tmp.index = tmp.index -> prev;
                if(tmp.index -> prev == NULL){
                    throw index_out_of_bound();
                    break;
                }
            }
            return tmp;
            //TODO
        }
        // return th distance between two iterator,
        // if these two iterators points to different vectors, throw invaild_iterator.
        int operator-(const const_iterator &rhs) const {
            int num = 0;
            node * tmp = index;
            while(tmp -> prev -> prev != NULL){
                tmp = tmp -> prev;
                num++;
                if(tmp == rhs.index){
                    return num;
                }
            }
            tmp = index;
            num = 0;
            while(tmp -> next -> next != NULL){
                tmp = tmp -> next;
                num--;
                if(tmp == rhs.index){
                    return num;
                }
            }
            throw invalid_iterator();            //TODO
        }
        const_iterator operator+=(const int &n) {
            for(int i = 1 ; i <= n; ++i){
                index = index -> next;
                if(index -> next == NULL){
                    throw index_out_of_bound();
                    break;
                }
            }
            return *this;
            //TODO
        }
        const_iterator operator-=(const int &n) {
            for(int i = 1 ; i <= n; ++i){
                index = index -> prev;
                if(index -> prev == NULL){
                    throw index_out_of_bound();
                    break;
                }
            }
            return *this;
            //TODO
        }
        /**
         * TODO iter++
         */
        const_iterator operator++(int) {
            const_iterator tmp(index);
            index = index -> next;
            if(index -> next == NULL) throw index_out_of_bound();
            return tmp;
        }
        /**
         * TODO ++iter
         */
        const_iterator& operator++() {
            index = index -> next;
            if(index -> next == NULL) throw index_out_of_bound();
            return * this;
        }
        /**
         * TODO iter--
         */
        const_iterator operator--(int) {
            const_iterator tmp(index);
            index = index -> prev;
            if(index -> prev == NULL) throw index_out_of_bound();
            return tmp;
        }
        /**
         * TODO --iter
         */
        const_iterator& operator--() {
            index = index -> prev;
            if(index  -> prev == NULL) throw index_out_of_bound();
            return * this;
        }
        /**
         * TODO *it
         */
        T& operator*() const{
            return index -> value;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory).
         */
        bool operator==(const const_iterator &rhs) const {
            if(index == rhs -> index) return true;
            else{
                return false;
            }
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const const_iterator &rhs) const {
            if(index == rhs.index) return false;
            else{
                return true;
            }
        }
    };

    /**
     * TODO Constructs
     * Atleast three: default constructor, copy constructor and a constructor for std::list
     */
    list() {
        head = new node;
        tail = new node;
        head -> next = tail;
        tail -> prev = head;
        currentlength = 0;
    }
    /*  //original version
	list(const std::fstream &f) {
        out.open("f");
        std::ifstream in("f");
        int num;
        T tmp;
        head = new node;
        tail = new node;
        head -> next = tail;
        tail -> prev = head;
        currentlength = 0;
        in.read(reinterpret_cast<char*>(& num), sizeof(int));
        for(int i = 1; i <= num; ++i){
            in.read(reinterpret_cast<char*>(&tmp), sizeof(T));
            push_back(tmp);
        }
        in.close();
    }
	*/
    list(const list & other){
        head = new node;
        tail = new node;
        head -> next = tail;
        tail -> prev = head;
        currentlength = 0;
        for(int i = 0; i < other.size(); ++i){
            push_back(other[i]);
        }
    }
    /**
     * TODO Destructor
     */
	~list() {
        for(int i = 1;i <= currentlength; ++i){
            pop_front();
        }
        delete head;
        delete tail;
	}
	/* original version
    ~list() {
        out.write(reinterpret_cast<char*>(&currentlength), sizeof(int));
        T tmp;
        for(int i = 1;i <= currentlength; ++i){
            tmp = head -> next -> value;
            pop_front();
            out.write(reinterpret_cast<char*>(&tmp), sizeof(T));
        }
        out.close();
        delete head;
        delete tail;
    }
	*/
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     * !!! Pay attentions
     *   In STL this operator does not check the boundary but I want you to do.
     */
	void readIn(const std::string &fileName) {
		if(!empty()) throw container_is_not_empty();
		io.open(fileName, std::fstream::in);
		if(!io) throw no_such_file();
		int _currentlength;
		io.read(reinterpret_cast<char *> (&_currentlength), sizeof(int));
		T x;
		//std::cout << _currentlength << std::endl;
		for(int i = 0; i < _currentlength; ++i) {
			io.read(reinterpret_cast<char *> (&x), sizeof(T));
			//std::cout << x << std::endl;
			push_back(x);
		}
	}
	void writeOut(const std::string &fileName) {
		if(io) io.close();
		io.open(fileName, std::fstream::out | std::fstream::binary);
		if(!io) throw no_such_file();
		io.write(reinterpret_cast<const char *> (&currentlength), sizeof(int));
		node *ptr = head -> next;
		while(ptr != tail) {
			std::cout << ptr -> value << std::endl;
			io.write(reinterpret_cast<const char*> (&(ptr -> value)), sizeof(T));
			ptr = ptr -> next;
		}
	}
    list & operator = (const list & other){
        clear();
        for(int i = 0; i < other.size(); ++i){
            push_back(other[i]);
        }
        return * this;
    }
    T & operator[](const size_t &pos) {
        if(pos < 0 || pos >= currentlength) throw index_out_of_bound();
        node * tmp = head;
        for(int i = 0; i <= pos; ++i){
            tmp = tmp -> next;
        }
        return tmp -> value;
    }
    const T & operator[](const size_t &pos) const {
        if(pos >= size() || pos < 0) throw index_out_of_bound();
        node * tmp = head;
        for(int i = 0; i <= pos; ++i){
            tmp = tmp -> next;
        }
        return tmp -> value;
    }
    /**
     * access the first element.
     * throw container_is_empty if size == 0
     */
    const T & front() const {
        if(currentlength == 0) throw container_is_empty();
        return head -> next -> value;
    }
    /**
     * access the last element.
     * throw container_is_empty if size == 0
     */
    const T & back() const {
        if(currentlength == 0) throw container_is_empty();
        return tail -> prev -> value;
    }
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() {
        if(currentlength == 0) throw container_is_empty();
        iterator tmp(head -> next);
        return tmp;
    }
    iterator end() {
        if(currentlength == 0) throw container_is_empty();
        iterator tmp(tail -> prev);
        return tmp;
    }
    const_iterator cbegin()const{
        if(currentlength == 0) throw container_is_empty();
        const_iterator tmp(head -> next);
        return tmp;
    }
    const_iterator cend()const{
        if(currentlength == 0) throw container_is_empty();
        const_iterator tmp(tail -> prev);
        return tmp;
    }
    /**
     * checks whether the container is empty
     */
    bool empty() const {
        if(currentlength == 0){
            return true;
        }
        else{
            return false;
        }
    }
    /**
     * returns the number of elements
     */
    size_t size() const {
        return currentlength;
    }
    /**
     * clears the contents
     */
    void clear() {
        if(currentlength == 0){
            return ;
        }
        while(currentlength != 0){
            node * tmp = tail -> prev;
            node * before = tmp -> prev;
            node * after = tmp -> next;
            before -> next = tmp -> next;
            after -> prev = tmp -> prev;
            delete tmp;
            --currentlength;
        }
    }
    /**
     * inserts value before pos
     * returns an iterator pointing to the inserted value.
     */
    iterator insert(iterator pos, const T &value) {
        node * tmp = new node(value, pos.index, pos.index -> prev);
        pos.index -> prev -> next = tmp;
        currentlength ++;
        pos.index -> prev = tmp;
        return (--pos);
    }
    /**
     * inserts value at index ind.
     * after inserting, this->at(ind) == value is true
     * returns an iterator pointing to the inserted value.
     * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
     */
    iterator insert(const size_t &ind, const T &value) {
        if(ind > currentlength || ind < 0) throw index_out_of_bound();
        currentlength ++;
        if(ind == currentlength - 1){
            push_back(value);
            return end();
        }
        iterator tmp = begin();
        tmp += ind;
        return insert(tmp, value);
    }
    /**
     * removes the element at pos.
     * return an iterator pointing to the following element.
     * If the iterator pos refers the last element, the end() iterator is returned.
     */
    iterator erase(iterator pos) {
        node * tmp = pos.index;
        tmp -> prev -> next = tmp -> next;
        tmp -> next -> prev = tmp -> prev;
        if(tmp -> next == tail){
            pos--;
        }
        else{
            pos++;
        }
        delete tmp;
        currentlength --;
        return pos;
    }
    /**
     * removes the element with index ind.
     * return an iterator pointing to the following element.
     * throw index_out_of_bound if ind >= size
     */
    iterator erase(const size_t &ind) {
        if(ind >= currentlength || ind < 0) throw index_out_of_bound();
        iterator tmp = begin();
        tmp += ind;
        return erase(tmp);
    }
    /**
     * adds an element to the end/begin.
     */
    void push_back(const T &value) {
        node * tmp = tail -> prev;
        tail -> prev = new node(value, tail, tmp);
        tmp -> next = tail -> prev;
        ++currentlength;
    }
    void push_front(const T &value) {
        node * tmp = head -> next;
        head -> next = new node(value, tail, tmp);
        tmp -> prev = head -> next;
        ++currentlength;
    }
    /**
     * remove the last element from the end/begin.
     * throw container_is_empty if size() == 0
     */
    void pop_back() {
        if(currentlength == 0){
            throw container_is_empty();
        }
        /*if(currentlength == 10){
            node * tmp = tail -> prev;
            node * before = tmp -> prev;
            node * after = tmp -> next;
            before -> next = tmp -> next;
            after -> prev = tmp -> prev;
            delete tmp;
            --currentlength;
            return;
        }*/
        node * tmp = tail -> prev;
        node * before = tmp -> prev;
        node * after = tmp -> next;
        before -> next = tmp -> next;
        after -> prev = tmp -> prev;
        delete tmp;
        --currentlength;
    }
    void pop_front() {
        if(currentlength == 0) throw container_is_empty();
        node * tmp = head -> next;
        tmp -> prev -> next = tmp -> next;
        tmp -> next -> prev = tmp -> prev;
        delete tmp;
        --currentlength;
    }
};
}

#endif /* list_hpp */
