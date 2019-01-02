/*
 * Trie.h
 *
 *  Created on: 09.12.2018
 *      Author: Olenka
 */
#include <string>
#include <list>
#include <map>
#include <iostream>
#include <unistd.h>
#include <stack>

#ifndef TRIE_H_
#define TRIE_H_

using namespace std;

template<class T, class E = char>
class Trie {

public:
	typedef basic_string<E> key_type;           // string=basic_string<char>
	typedef pair<const key_type, T> value_type;
	typedef T mapped_type;
private:
	static int& cnt() {
		static int counter = 0;
		return counter;
	}

public:
	// The setter uses the fact that val()
	// returns a non-const reference,
	// so we can assign to it.
	static void set_cnt(const int _c) {
		cnt() = _c;
	}

	// A true getter.
	// Returns const int&, so we cannot assign to it.
	static const int& get_cnt() {
		return cnt();
	}

	class Node {
	public:
		virtual void print() = 0;
	};

	class LeafNode: public Node {
		typedef T mapped_type;

	private:
		mapped_type my_value;
	public:
		void print() {

			for (int j = 0; j < get_cnt(); ++j) {
				cout << ' ';
			}
			cout << ':';
			cout << this->my_value << endl;
			cout << endl;
			set_cnt(0);
		}
		bool isInnerNode() {
			return false;
		}
		void setValue(mapped_type value) {
			this->my_value = value;
		}
		mapped_type getValue() {
			return this->my_value;
		}
	};

	class InnerNode: public Node {
	private:
		std::map<E, Node*> childrenMap;

	public:
		std::map<E, Node*>* getChildrenMap() {
			return &(this->childrenMap);
		}

		void insertNode(key_type& word, const T &val) { //key_type basic_string
			if (word.length() == 0) {
				LeafNode* leaf = new LeafNode();
				leaf->setValue(val);
				this->childrenMap.insert(
						std::make_pair('\0', static_cast<Node*>(leaf)));
				return;
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
				node->insertNode(word, val);
			}
		}

		void print() {
			for (auto i = childrenMap.begin(); i != childrenMap.end(); i++) {

				if (i->first != '\0') {
					for (int j = 0; j < get_cnt(); ++j) {
						cout << ' ';
					}
					int cnt = get_cnt() + 1;
					set_cnt(cnt);

					cout << i->first << endl;
				} else {
					cout << ' ';
				}

				i->second->print();
			}
		}
	};

	class TrieIterator {
		typedef TrieIterator iterator;
		LeafNode* leafNode;
	public:
		TrieIterator(InnerNode* node) {
//			cout << "in constructor" << endl;
			if (node != NULL) {
				leafNode = static_cast<LeafNode*>(slideLeft(node));
			} else {
				leafNode = NULL;
			}
		}
		;

		LeafNode& operator *() {
			return *leafNode;
		}
		;
//		iterator& operator =(const iterator& rhs) {
//		}
//		;
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
//				cout << "while"<< my_stack.size() << endl;
				if (!my_stack.empty()) {
					it = my_stack.top();
					itEnd = my_end.top();
					//cout << it->first << " " << my_stack.size() << endl;
					it++;
				} else {
//					cout << "trying to create constr for null node" << endl;
					leafNode = NULL;
//					cout << "finished cnstr"<< endl;
					return *this; //points at the trie end
				}
			}
			my_stack.pop();
			my_end.pop();
			my_stack.push(it);
			my_end.push(itEnd);
			InnerNode* in = static_cast<InnerNode*>(it->second);
//			TrieIterator* newIt = new TrieIterator(in);
			leafNode = slideLeft(in);
//			(*(*newIt)).print();
			return *this;
		}
		;
		iterator operator ++(int) {
			return operator ++();
		}
		;

		std::stack<typename map<E, Node*>::iterator> my_stack;
		std::stack<typename map<E, Node*>::iterator> my_end;

		LeafNode* slideLeft(InnerNode* node) {
			LeafNode* ret = NULL;
			typename std::map<E, Node*>::iterator it =
					node->getChildrenMap()->begin(); //childrenMap.begin();
			typename std::map<E, Node*>::iterator itEnd =
					node->getChildrenMap()->end();
			while (it != itEnd) {
				my_stack.push(it);
//				cout << "letter to be pushed " << it->first << " " <<  endl;
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

	};
	typedef TrieIterator iterator;

	void print() {
		root.print();
	}

//	  void erase(const key_type& value); next step
//	  void clear();  // erase all
//iterator lower_bound(const key_type& testElement);  // first element >= testElement
//iterator upper_bound(const key_type& testElement);  // first element  >  testElement
//	  iterator find(const key_type& testElement);    // first element == testElement

	iterator begin() {
		iterator* it = new TrieIterator(&root);
		return *it;
	}
	;  // returns end() if not found
	iterator end() {
		iterator* it = new TrieIterator(NULL);
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
	InnerNode root; // attribut der klasse trie

public:

public:
	void insert(const value_type& value) {
		key_type key = value.first;
		T data = value.second;
		root.insertNode(key, data);
	}
	;

	InnerNode* getRoot() {
		return &root;
	}

	void iterate() {
		//sildeLeft;
		//++
		// treeIterator;
		//mapIterator;
		// bei der wurzel anfangen
		//0. slideLeft bis zum blatt; weg im stack merken

		//1.pops_stack; kindermap zur�ckgeben, in der der Node liegt, auf den der pointer zeigt,
		//2.in der map  mapiterator++;
		//3. zegt der mapiterator auf das ende?
		//nein -> schritte 0-3 wiederholen
		//ja->1-3 wiederholen
		//das ganze solange bis der iterator auf die wurzel zeigt

	}

};

//		void print() {
//			Node* n = this;
//			std::list<Node*> visited; //speichert alle buchstaben
//			while (n->hasParent()) {
//				visited.push_front(n);
//				n = n->getParentNode();
//			}
//			typename std::list<Node*>::iterator it;
//			int spaces = 0;
//			for (it = visited.begin(); it != visited.end(); ++it) {
//				for (int i = 0; i < spaces; ++i) {
//					std::cout << ' ';
//				}
//				spaces += 2;
//				std::cout << (*it)->getKey() << std::endl;
//			}
//			for (int i = 0; i < spaces; ++i) {
//				std::cout << ' ';
//			}
//
//			std::cout << this->my_value << std::endl;
//		}

#endif /* TRIE_H_ */
