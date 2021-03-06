/*
 * Trie.h
 *
 *  Created on: 09.12.2018
 *      Author: Olga Nikoliai, Nicole Johnson
 */
#include <string>
#include <list>
#include <map>
#include <iostream>
#include <stack>
#include <string.h>
#include <list>

#ifndef TRIE_H_
#define TRIE_H_

using namespace std;

template<class T, class E = char>
class Trie {

public:
	typedef basic_string<E> key_type;           // string=basic_string<char>
	typedef pair<const key_type, T> value_type;
	typedef T mapped_type;


public:

/**
 *  class representing nodes
 */
	class Node {
	public:
		virtual void printNode(int cnt) = 0;
	};
/**
 * class representing leaf nodes
 */
	class LeafNode: public Node {
		typedef T mapped_type;

	private:
		mapped_type my_value;
	public:
		/**
		 * prints a leaf node
		 */
		void printNode(int cnt) {

			for (int j = 0; j < cnt; ++j) {
				cout << ' ';
			}
			cout << ':';
			cout << this->my_value << endl;
			cout << endl;
		}
/**
 * setter for value
 */
		void setValue(mapped_type value) {
			this->my_value = value;
		}
		/**
		 * getter for value
		 */
		mapped_type getValue() {
			return this->my_value;
		}
	};
/**
 * class representing inner nodes
 */
	class InnerNode: public Node {
	private:
		std::map<E, Node*> childrenMap;

	public:
		std::map<E, Node*>* getChildrenMap() {
			return &(this->childrenMap);
		}
/**
 * inserts inner node in a trie
 */
		LeafNode* insertNode(key_type& word, const T &val) { //key_type basic_string
			LeafNode* leaf = new LeafNode();
			if (word.length() == 0) {
				leaf->setValue(val);
				this->childrenMap.insert(
						std::make_pair('\0', static_cast<Node*>(leaf)));
				return leaf;
			}
			E letter = word.at(0);
			InnerNode* node;
			typename std::map<E, Node*>::iterator newNode =
					this->childrenMap.find(letter);
			if (newNode == this->childrenMap.end()) { //letter doesnt exist in the map, need to create
				node = new InnerNode();
				this->childrenMap.insert(std::make_pair(letter, node));
			} else {
				node = static_cast<InnerNode*>((*newNode).second);
			}
			if (word.length() != 0) { // l�nge anfragen (basic sting leer?)
				key_type temp = word.substr(1, word.length() - 1);
				word = temp;
				leaf = node->insertNode(word, val);
			}
			return leaf;
		}
/**
 * prints an inner node
 */
		void printNode(int cnt) {
			for (auto i = childrenMap.begin(); i != childrenMap.end(); i++) {

				if (i->first != '\0') {
					for (int j = 0; j < cnt; ++j) {
						cout << ' ';
					}

					cout << i->first << endl;
				}

				i->second->printNode(cnt + 1);
			}
		}
	};
/**
 * iterator for tries
 */
	class TrieIterator {
		typedef TrieIterator iterator;
		typedef std::pair<key_type, LeafNode*> return_t;
		LeafNode* leafNode;
		key_type key;
	public:
/**
 * constructor for iterator
 */
		TrieIterator(InnerNode* in) :
				leafNode(NULL) {
			setPair(in);
		}
		;
		/**
		 * constructor for iterator
		 */
		TrieIterator(LeafNode* leaf, key_type input_key) {
			leafNode = leaf;
			key = input_key;
		}
		;
/**
 * defines leaf node and key for an inner node
 */
		void setPair(InnerNode* in) {
			key = "";
			if (in != NULL) {
				leafNode = slideLeft(in);
				while (!my_stack.empty()) {
					my_list.push_front(my_stack.top());
					key = my_stack.top()->first + key;
					my_stack.pop();
				}
				while (!my_list.empty()) {
					my_stack.push(my_list.front());
					my_list.pop_front();
				}
			} else {
				leafNode = NULL;
			}
		}
		;

		return_t operator *() {
			return return_t(key, leafNode);
		}
		;
		iterator& operator =(const iterator& rhs) {
			return (this->leafNode = rhs.leafNode);
		}
		;
		bool operator !=(const iterator& rhs) const {
			return (this->leafNode != rhs.leafNode);
		}
		;
		bool operator ==(const iterator& rhs) const {
			return (this->leafNode == rhs.leafNode);
		}
		;
		iterator& operator ++() {
			typename std::map<E, Node*>::iterator it = my_stack.top();
			typename std::map<E, Node*>::iterator itEnd = my_end.top();
			it++;
			while (it == itEnd) {
				my_stack.pop();
				my_end.pop();
				if (!my_stack.empty()) {
					it = my_stack.top();
					itEnd = my_end.top();
					it++;
				} else {
					leafNode = NULL;
					return *this; //points at the trie end
				}
			}
			my_stack.pop();
			my_end.pop();
			my_stack.push(it);
			my_end.push(itEnd);
			InnerNode* in = static_cast<InnerNode*>(it->second);

			setPair(in);
			return *this;
		}
		;
		iterator operator ++(int) {
			return operator ++();
		}
		;

		std::list<typename map<E, Node*>::iterator> my_list;
		std::stack<typename map<E, Node*>::iterator> my_stack;
		std::stack<typename map<E, Node*>::iterator> my_end;
/**
 * implements the "slide left leaf" logic
 */
		LeafNode* slideLeft(InnerNode* node) {
			LeafNode* ret = NULL;
			typename std::map<E, Node*>::iterator it =
					node->getChildrenMap()->begin(); //childrenMap.begin();
			typename std::map<E, Node*>::iterator itEnd =
					node->getChildrenMap()->end();
			while (it != itEnd) {
				my_stack.push(it);
				my_end.push(itEnd);
				if (it->first == '\0') {
					LeafNode* ret = static_cast<LeafNode*>(it->second);
					return ret;
				}
				node = static_cast<InnerNode*>(it->second);
				it = node->getChildrenMap()->begin();
				itEnd = node->getChildrenMap()->end();
			}
			return ret;
		}
		std::stack<typename map<E, Node*>::iterator> get_my_stack() {
			return my_stack;

		}

	};
	typedef TrieIterator iterator;
/**
 * prints a tree
 */
	void print() {
		root.printNode(0);
	}
	;
	bool empty() const {
		return this->root.childrenMap.empty();
	}
	;
	/**
	 * erases a node for a given key
	 */
	void erase(const key_type& value) {
		iterator it_pair = find(value);
		if (it_pair != this->end()) {
			std::stack<typename map<E, Node*>::iterator> my_stack =
					it_pair.get_my_stack();
			E keyToDel = my_stack.top()->first;
			my_stack.pop();
			InnerNode* node = (InnerNode*) my_stack.top()->second;
			while (my_stack.size() > 0) {
				node->getChildrenMap()->erase(keyToDel);
				if (node->getChildrenMap()->empty()) {
					node = NULL;
					keyToDel = my_stack.top()->first;
					my_stack.pop();
					if (!my_stack.empty()) {
						node = (InnerNode*) my_stack.top()->second;
					}
				} else {
					return;
				}
			}
			root.getChildrenMap()->erase(keyToDel);
		}
	}
	;
	/**
	 * erases a tree
	 */
	void clear() {
		for (auto it = this->begin(); it != this->end();) {
			key_type key = (*it).first;
			it++;
			erase(key);
		}
	}
	;
	iterator lower_bound(const key_type& testElement) {
		return find(testElement);
	}
	;
	iterator upper_bound(const key_type& testElement) {
		iterator it = find(testElement);
		iterator it2 = it;
		while (it != end()) {
			it2++;
			if (it2 != it) {
				return it2;
			}
		}
		return end();
	}
	;
	/**
	 * find a node for a given key
	 */
	iterator find(const key_type& testElement) {
		iterator it = this->begin();
		while (it != this->end()) {
			if ((*it).first == testElement) {
				return it;
			}
			it++;
		}
		return it;
	}
	;

	iterator begin() {
		iterator* it = new TrieIterator(&root);
		return *it;
	}
	;

	iterator end() {
		iterator* it = new TrieIterator((InnerNode*) NULL);
		return *it;
	}
	;

	Trie() {
	}
	;

	virtual ~Trie() {
	}
	;
private:
	InnerNode root;


public:
	/**
	 * inserts a new node in a tree
	 */
	iterator insert(const value_type& value) {
		key_type key = value.first;
		key_type keyToRet = key;
		T data = value.second;
		LeafNode* leaf = root.insertNode(key, data);
		iterator* it = new iterator(leaf, keyToRet);
		return *it;
	}
	;
/**
 * getter for a root
 */
	InnerNode* getRoot() {
		return &root;
	}

};

#endif /* TRIE_H_ */
