#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

#include <functional>
#include <cstddef>
#include <iostream>
#include "utility.hpp"
#include "exceptions.hpp"
#include "rwInt.hpp"

namespace sjtu {
	
template<
	class Key,
	class T,
	class Compare = std::less<Key>
> class map {
public:
	typedef pair<const Key, T> value_type;
	class node {
	public:
		node *las,*nex,*ls,*rs,*fa;
		int height,size,id;
		value_type *data;
		node(const value_type &v,node *la = NULL,node *ne = NULL,node *f = NULL)
			:las(la),nex(ne),fa(f),ls(NULL),rs(NULL),size(1) {
			data = new value_type(v);
		}
		node()
			:data(NULL),las(NULL),nex(NULL),fa(NULL),ls(NULL),rs(NULL),size(1){}
		~node() {if (data != NULL) delete data;}
	};
private:
	node *root,*be,*en;
	int siz;
	Compare cmp;
	int max(int i,int j) {return i > j ? i : j;}
	int height(node *x) {return x == NULL ? -1 : x -> height;}
	int size(node *x) {return x == NULL ? 0 : x -> size;}
public:
	class const_iterator;
	class iterator {
		friend map;
	private:
		 node *pos;
		 map *mp;
	public:
		iterator(map *m = NULL,node *x = NULL) :mp(m),pos(x){}
		iterator(const iterator &other) :mp(other.mp),pos(other.pos){}
		iterator operator++(int) {
			if (pos == NULL || pos -> nex == NULL) throw invalid_iterator();
			iterator t = *this;
			pos = pos -> nex;
			return t;
		}
		iterator & operator++() {
			if (pos == NULL || pos -> nex == NULL) throw invalid_iterator();
			pos = pos -> nex;
			return *this;
		}
		iterator operator--(int) {
			if (pos == NULL || pos -> las == NULL || pos -> las -> las == NULL) throw invalid_iterator();
			iterator t = *this;
			pos = pos -> las;
			return t;
		}
		iterator & operator--() {
			if (pos == NULL || pos -> las == NULL || pos -> las -> las == NULL) throw invalid_iterator();
			pos = pos -> las;
			return *this;
		}
		value_type & operator*() const {return *(pos -> data);}
		bool operator==(const iterator &rhs) const {return pos == rhs.pos;}
		bool operator==(const const_iterator &rhs) const {return pos == rhs.pos;}
		bool operator!=(const iterator &rhs) const {return pos != rhs.pos;}
		bool operator!=(const const_iterator &rhs) const {return pos != rhs.pos;}
		value_type* operator->() const noexcept {return pos -> data;}
	};
	class const_iterator {
		friend map;
	private:
		const node *pos;
		const map *mp;
	public:
		const_iterator(map *m = NULL,node *x = NULL) :mp(m),pos(x){}
		const_iterator(const const_iterator &other) :mp(other.mp),pos(other.pos){}
		const_iterator(const iterator &other) :mp(other.mp),pos(other.pos){}
		const_iterator operator++(int) {
			if (pos == NULL || pos -> nex == NULL) throw invalid_iterator();
			const_iterator t = *this;
			pos = pos -> nex;
			return t;
		}
		const_iterator & operator++() {
			if (pos == NULL || pos -> nex == NULL) throw invalid_iterator();
			pos = pos -> nex;
			return *this;
		}
		const_iterator operator--(int) {
			if (pos == NULL || pos -> las == NULL || pos -> las -> las == NULL) throw invalid_iterator();
			const_iterator t = *this;
			pos = pos -> las;
			return t;
		}
		const_iterator & operator--() {
			if (pos == NULL || pos -> las == NULL || pos -> las -> las == NULL) throw invalid_iterator();
			pos = pos -> las;
			return *this;
		}
		value_type & operator*() const {return *(pos -> data);}
		bool operator==(const iterator &rhs) const {return pos == rhs.pos;}
		bool operator==(const const_iterator &rhs) const {return pos == rhs.pos;}
		bool operator!=(const iterator &rhs) const {return pos != rhs.pos;}
		bool operator!=(const const_iterator &rhs) const {return pos != rhs.pos;}
		value_type* operator->() const noexcept {return pos -> data;}
	};
	void travel(node *p) {
		std::cout << "travel " << p << " @@@ " << p -> data -> second << ' ';
		if (p -> ls == NULL) std::cout << "X ";
		else std::cout << p -> ls << ' ' << p -> ls -> data -> second << ' ';
		if (p -> rs == NULL) std::cout << "X ";
		else std::cout << p -> rs << ' ' << p -> rs -> data -> second << ' ';
		if (p -> fa == NULL) std::cout << "X\n";
		else std::cout << p -> fa << ' ' << p -> fa -> data -> second << std::endl;
		if (p -> ls != NULL) travel(p -> ls);
		if (p -> rs != NULL) travel(p -> rs);
	}
	void travel() {
		if (root != NULL) travel(root);
		puts("");
	}
	map() {
		root = NULL;
		be = new node();en = new node();
		be -> nex = en;en -> las = be;
		siz = 0;
	}
	map(const map &other) {
		root = NULL;
		be = new node();en = new node();
		be -> nex = en;en -> las = be;
		siz = 0;
		if (other.siz) {
			node **Q = new node*[other.siz],*p;
			int head,tail;
			head = tail = 0;
			Q[tail++] = other.root;
			while (head != tail) {
				p = Q[head++];
				insert(*(p -> data));
				if (p -> ls != NULL) Q[tail++] = p -> ls;
				if (p -> rs != NULL) Q[tail++] = p -> rs;
			}
			delete [] Q;
		}
	}
	void clear()
	{
		if (siz) {
			node **Q = new node*[siz],*p;
			int head,tail;
			head = tail = 0;
			Q[tail++] = root;
			while (head != tail) {
				p = Q[head++];
				if (p -> ls != NULL) Q[tail++] = p -> ls;
				if (p -> rs != NULL) Q[tail++] = p -> rs;
				delete p;
			}
			delete [] Q;
		}
		be -> nex = en;en -> las = be;
		root = NULL;
		siz = 0;
	}
	map & operator=(const map &other) {
		if (this == &other) return *this;
		clear();
		if (other.siz) {
			node **Q = new node *[other.siz],*p;
			int head,tail;
			head = tail = 0;
			Q[tail++] = other.root;
			while (head != tail) {
				p = Q[head++];
				insert(*(p -> data));
				if (p -> ls != NULL) Q[tail++] = p -> ls;
				if (p -> rs != NULL) Q[tail++] = p -> rs;
			}
			delete [] Q;
		}
		return *this;
	}
	~map() {
		clear();
		delete be;
		delete en;
	}
	T & at(const Key &key) {
		node *p = root;
		while (p != NULL) {
			if (!(cmp(p -> data -> first,key) || cmp(key,p -> data -> first))) return p -> data -> second;
			if (cmp(key,p -> data -> first)) p = p -> ls;
			else p = p -> rs;
		}
		throw index_out_of_bound();
	}
	const T & at(const Key &key) const {
		node *p = root;
		while (p != NULL) {
			if (!(cmp(p -> data -> first,key) || cmp(key,p -> data -> first))) return p -> data -> second;
			if (cmp(key,p -> data -> first)) p = p -> ls;
			else p = p -> rs;
		}
		throw index_out_of_bound();
	}
	iterator begin() {
		if (be == NULL) throw invalid_iterator();
		iterator rtn;rtn.mp = this;rtn.pos = be -> nex;return rtn;
	}
	const_iterator cbegin() const {
		if (be == NULL) throw invalid_iterator();
		const_iterator rtn;rtn.mp = this;rtn.pos = be -> nex;return rtn;
	}
	iterator end() {
		if (en == NULL) throw invalid_iterator();
		iterator rtn;rtn.mp = this;rtn.pos = en;return rtn;
	}
	const_iterator cend() const {
		if (en == NULL) throw invalid_iterator();
		const_iterator rtn;rtn.mp = this;rtn.pos = en;return rtn;
	}
	bool empty() const {return siz == 0;}
	size_t size() const {return siz;}
	iterator find(const Key &key) {
		node *p = root;
		iterator rtn;
		while (p != NULL) {
			if (!(cmp(p -> data -> first,key) || cmp(key,p -> data -> first)))
			{
				rtn.mp = this;rtn.pos = p;
				return rtn;
			}
			if (cmp(key,p -> data -> first)) p = p -> ls;
			else p = p -> rs;
		}
		rtn.mp = this;rtn.pos = en;
		return rtn;
	}
	const_iterator find(const Key &key) const {
		node *p = root;
		const_iterator rtn;
		while (p != NULL) {
			if (!(cmp(p -> data -> first,key) || cmp(key,p -> data -> first))) {
				rtn.mp = this;rtn.pos = p;
				return rtn;
			}
			if (cmp(key,p -> data -> first)) p = p -> ls;
			else p = p -> rs;
		}
		rtn.mp = this;rtn.pos = en;
		return rtn;
	}
	void L(node *&q) {
		node *p = q -> ls,*r = q -> fa;
		q -> ls = p -> rs;
		if (p -> rs != NULL) p -> rs -> fa = q;
		p -> rs = q;
		q -> fa = p;
		q -> height = max(height(q -> ls),height(q -> rs)) + 1;
		p -> height = max(height(p -> ls),height(p -> rs)) + 1;
		q -> size = size(q -> ls) + size(q -> rs) + 1;
		p -> size = size(p -> ls) + size(p -> rs) + 1;
		q = p;
		p -> fa = r;
	}
	void R(node *&q) {
		node *p = q -> rs,*r = q -> fa;
		q -> rs = p -> ls;
		if (p -> ls != NULL) p -> ls -> fa = q;
		p -> ls = q;
		q -> fa = p;
		q -> height = max(height(q -> ls),height(q -> rs)) + 1;
		p -> height = max(height(p -> ls),height(p -> rs)) + 1;
		q -> size = size(q -> ls) + size(q -> rs) + 1;
		p -> size = size(p -> ls) + size(p -> rs) + 1;
		q = p;
		p -> fa = r;
	}
	pair<iterator, bool> insert(const value_type &value,node *&p,node *f) {
		if (p == NULL) {
			++siz;
			p = new node(value);
			if (p == f -> ls) {
				p -> nex = f;
				p -> las = f -> las;
				f -> las = p;
				if (p -> las != NULL) p -> las -> nex = p;
			}
			else {
				p -> las = f;
				p -> nex = f -> nex;
				f -> nex = p;
				if (p -> nex != NULL) p -> nex -> las = p;
			}
			p -> fa = f;
			p -> height = 0;
			return pair<iterator,bool>(iterator(this,p),1);
		}
		else
		{
			++(p -> size);
			if (cmp(value.first,p -> data -> first)) {
				pair<iterator,bool> rtn(insert(value,p -> ls,p));
				if (height(p -> ls) - height(p -> rs) == 2)
					if (cmp(value.first,p -> ls -> data -> first)) L(p);
					else R(p -> ls),L(p);
				p -> height = max(height(p -> ls),height(p -> rs)) + 1;
				return rtn;
			}
			else if (cmp(p -> data -> first,value.first)) {
				pair<iterator,bool> rtn(insert(value,p -> rs,p));
				if (height(p -> rs) - height(p -> ls) == 2) {
					if (cmp(p -> rs -> data -> first,value.first)) R(p);
					else L(p -> rs),R(p);
				}
				p -> height = max(height(p -> ls),height(p -> rs)) + 1;
				return rtn;
			}
			else return pair<iterator,bool>(iterator(this,p),0);
		}
	}
	pair<iterator, bool> insert(const value_type &value) {
		if (root == NULL) {
			be -> nex = en -> las = root = new node(value,be,en,NULL);
			root -> height = 0;
			++siz;
			pair<iterator,bool> rtn(iterator(this,root),1);
			return rtn;
		}
		return insert(value,root,NULL);
	}
	bool erase(const value_type &value,node *&p) {
		bool stop = 0;
		int subT;
		if (p == NULL) return 1;
		--(p -> size);
		if (cmp(value.first,p -> data -> first)) {stop = erase(value,p -> ls);subT = 1;}
		else if (cmp(p -> data -> first,value.first)) {stop = erase(value,p -> rs);subT = 2;}
		else if (p -> ls == NULL || p -> rs == NULL) {
			node *q = p;
			if (p -> las != NULL) p -> las -> nex = p -> nex;
			if (p -> nex != NULL) p -> nex -> las = p -> las;
			if (p -> ls != NULL) p = p -> ls;
			else p = p -> rs;
			if (p != NULL) p -> fa = q -> fa;
			delete q;
			return 0;
		}
		else {
			node *t = p -> rs,*q = p;
			while (t -> ls != NULL) t = t -> ls;
			p = t;
			if (p == q -> rs) {
				p -> las = q -> las;
				q -> las = p;
				q -> nex = p -> nex;
				p -> nex = q;
				if (p -> las != NULL) p -> las -> nex = p;
				if (q -> nex != NULL) q -> nex -> las = q;
				p -> fa = q -> fa;
				q -> fa = p;
				p -> ls = q -> ls;
				q -> ls = NULL;
				if (p -> ls != NULL) p -> ls -> fa = p;
				q -> rs = p -> rs;
				p -> rs = q;
				if (q -> rs != NULL) q -> rs -> fa = q;
				q -> height = p -> height;
				p -> height = max(height(p -> ls),height(p -> rs)) + 1;
				q -> size = p -> size;
				p -> size = size(p -> ls) + size(p -> rs) + 1;
			}
			else {
				p -> las = q -> las;
				q -> las = p;
				q -> nex = p -> nex;
				p -> nex = q;
				if (p -> las != NULL) p -> las -> nex = p;
				if (q -> nex != NULL) q -> nex -> las = q;
				t = p -> fa;
				p -> fa = q -> fa;
				q -> fa = t;
				q -> fa -> ls = q;
				p -> ls = q -> ls;
				q -> ls = NULL;
				if (p -> ls != NULL) p -> ls -> fa = p;
				t = p -> rs;
				p -> rs = q -> rs;
				q -> rs = t;
				if (p -> rs != NULL) p -> rs -> fa = p;
				if (q -> rs != NULL) q -> rs -> fa = q;
			}
			stop = erase(*(q -> data),p -> rs);
			subT = 2;
		}
		p -> height = max(height(p -> ls),height(p -> rs)) + 1;
		p -> size = size(p -> ls) + size(p -> rs) + 1;
		if (stop) return 1;
		int blc;
		if (subT == 1) {
			blc = height(p -> ls) - height(p -> rs) + 1;
			if (blc == 0) return 1;
			if (blc == 1) return 0;
			if (blc == -1) {
				int blcr = height(p -> rs -> rs) - height(p -> rs -> ls);
				if (blcr == 0) {R(p);return 1;}
				if (blcr == 1)	R(p);
				else L(p -> rs),R(p);
				return 0;
			}
		}
		else {
			blc = height(p -> rs) - height(p -> ls) + 1;
			if (blc == 0) return 1;
			if (blc == 1) return 0;
			if (blc == -1) {
				int blcl = height(p -> ls -> ls) - height(p -> ls -> rs);
				if (blcl == 0) {L(p);return 1;}
				if (blcl == 1) L(p);
				else R(p -> ls),L(p);
				return 0;
			}
		}
	}
	void erase(iterator it) {
		if (it.mp != this || it.pos == be || it.pos == en) throw invalid_iterator();
		--siz;
		erase(*it,root);
	}
	T & operator[](const Key &key) {
		node *p = root;
		while (p != NULL) {
			if (!(cmp(p -> data -> first,key) || cmp(key,p -> data -> first))) return p -> data -> second;
			if (cmp(key,p -> data -> first)) p = p -> ls;
			else p = p -> rs;
		}
		T v;
		return insert(value_type(key,v)).first -> second;
	}
	const T & operator[](const Key &key) const {
		node *p = root;
		while (p != NULL) {
			if (!(cmp(p -> data -> first,key) || cmp(key,p -> data -> first))) return p -> data -> second;
			if (cmp(key,p -> data -> first)) p = p -> ls;
			else p = p -> rs;
		}
		throw index_out_of_bound();
	}
	size_t count(const Key &key) const {
		node *p = root;
		while (p != NULL) {
			if (!(cmp(p -> data -> first,key) || cmp(key,p -> data -> first))) return 1;
			if (cmp(key,p -> data -> first)) p = p -> ls;
			else p = p -> rs;
		}
		return 0;
	}
	iterator find_kth_least_number(int k) {
		if (k < 1 || k > siz) throw index_out_of_bound();
		node *p = root;
		while (p != NULL) {
			if (k <= size(p -> ls)) p = p -> ls;
			else if (k > size(p -> ls) + 1) k -= size(p -> ls) + 1,p = p -> rs;
			else return iterator(this,p);
		}
		return iterator(this,p);
	}
	friend std::ifstream &operator>>(std::ifstream &file, map &obj) {
		if(!empty()) throw container_is_not_empty();
//		file.read(reinterpret_cast<char *> (&obj.siz), sizeof(int));
		file >> obj.siz;
		Key *s = new Key[obj.siz];
		for (int i = 0; i < obj.siz; ++i)
			file >> obj.s[i];
//			file.read(reinterpret_cast<char *> (&s[i]), sizeof(Key));
		T *v = new T[obj.siz];
		for (int i = 0; i < obj.siz; ++i)
			file >> obj.v[i];
//			v[i].readIn(file);
		node **n = new node *[obj.siz + 2];
		n[0] = obj.be;n[obj.siz + 1] = obj.en;
		for (int i = 0; i < obj.siz; ++i)
			n[i + 1] = new node(value_type(s[i],v[i]));
		obj.be -> nex = n[1];obj.obj.en -> las = n[obj.siz];
		int ls,rs,fa;
		for (int i = 1; i <= obj.siz; ++i) {
			file >> ls >> rs >> fa >> (n[i] -> size) >> (n[i] -> height);
			/*
			file.read(reinterpret_cast<char *> (&ls), sizeof(int));
			file.read(reinterpret_cast<char *> (&rs), sizeof(int));
			file.read(reinterpret_cast<char *> (&fa), sizeof(int));
			file.read(reinterpret_cast<char *> (&(n[i] -> size)), sizeof(int));
			file.read(reinterpret_cast<char *> (&(n[i] -> height)), sizeof(int));
			*/
			n[i] -> ls = (ls != 0 ? n[ls] : NULL);
			n[i] -> rs = (rs != 0 ? n[rs] : NULL);
			n[i] -> fa = (fa != 0 ? n[fa] : NULL);
			n[i] -> las = n[i - 1];n[i] -> nex = n[i + 1];
		}
		int rt;
//		file.read(reinterpret_cast<char *> (&rt), sizeof(int));
		file >> rt;
		obj.root = n[rt];
		delete [] s;delete [] v;delete [] n;
		return file;
	}
    friend std::ofstream &operator<<(std::ofstream &file, map &obj) {
    	file << obj.siz;
//		file.write(reinterpret_cast<const char *> (&siz), sizeof(int));
		iterator it = obj.begin();
		for (int i = 0; i < obj.siz; ++i,++it)
			file << (it -> first);
//			file.write(reinterpret_cast<const char *> (&((*it).fisrt))), sizeof(int));
		it = obj.begin();
		for (int i = 0; i < obj.siz; ++i,++it)
			file << (it -> second);
//			file.write(reinterpret_cast<const char *> (&((*it).second)), sizeof(T));
		it = obj.begin();
		for (int i = 1; it != obj.end(); ++i,++it) it.pos -> id = i;
		for (it = obj.begin(); it != obj.end(); ++it) {
			file << (it.pos -> ls -> id) << (it.pos -> rs -> id) << (it.pos -> fa -> id) << (it.pos -> size) << (it.pos -> height);
			/*
			file.write(reinterpret_cast<const char *> (&(it.pos -> ls -> id)), sizeof(int));
			file.write(reinterpret_cast<const char *> (&(it.pos -> rs -> id)), sizeof(int));
			file.write(reinterpret_cast<const char *> (&(it.pos -> fa -> id)), sizeof(int));
			file.write(reinterpret_cast<const char *> (&(it.pos -> size)), sizeof(int));
			file.write(reinterpret_cast<const char *> (&(it.pos -> height)), sizeof(int));
			*/
		}
		file << (obj.root -> id);
//		file.write(reinterpret_cast<const char *> (&(root -> id)), sizeof(int));
		return file;
	}
};

}
#endif
