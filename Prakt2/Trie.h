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
	};

	class InnerNode: public Node {
	private:
		std::map<E, Node*> childrenMap;

	public:
		std::map<E, Node*> getChildrenMap() {
			return childrenMap;
		}

		void insertNode(key_type& word, const T &val) { //key_type basic_string
			if (word.length() == 0) {
				LeafNode* leaf = new LeafNode();
				leaf->setValue(val);
				childrenMap.insert(
						std::make_pair('\0', static_cast<Node*>(leaf)));
				return;
			}
			E letter = word.at(0);
			InnerNode* node;
			auto newNode = childrenMap.find(letter);
			if (newNode == childrenMap.end()) { //letter doesnt exist in the map, need to create
				node = new InnerNode();
				childrenMap.insert(std::make_pair(letter, node));
			} else {
				node = static_cast<InnerNode*>((*newNode).second);
			}
			if (word.length() != 0) { // länge anfragen (basic sting leer?)
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
				}else{
					cout << ' ';
				}

				i->second->print();
			}
		}
	};

//	  bool empty() const;

	class TrieIterator {
		typedef TrieIterator iterator;
	public:
		value_type& operator *() {
		}
		;
		iterator& operator =(const iterator& rhs) {

		}
		;
		bool operator !=(const iterator& rhs) const {
		}
		;
		bool operator ==(const iterator& rhs) const {
		}
		;
		iterator& operator ++() {

		}
		;
		iterator operator ++(int) {

		}
		;

		std::stack<typename map<E, Node*>::iterator> my_stack;
		std::stack<typename map<E, Node*>::iterator> my_end;

		void slideLeft(InnerNode* node) {
			auto it = node->childrenMap.begin();
			auto itEnd = node->childrenMap.end();
			while (it != itEnd) {
				my_stack.push(it);//i
				my_end.push(itEnd);//0x55678
				if (it->first == '\0') {
					node = static_cast<LeafNode*>(it->second);
					return;
				}
				node = static_cast<InnerNode*>(it->second);//inner node with i
				it = node->childrenMap.begin();//pointer <char, Node*> r, node with r
				itEnd = node->childrenMap.end();//0x4556
			}
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
	}
	;  // returns end() if not found
	iterator end() {
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

	void iterate() {
		//sildeLeft;
		//++
		// treeIterator;
		//mapIterator;
		// bei der wurzel anfangen
		//0. slideLeft bis zum blatt; weg im stack merken

		//1.pops_stack; kindermap zurückgeben, in der der Node liegt, auf den der pointer zeigt,
		//2.in der map  mapiterator++;
		//3. zegt der mapiterator auf das ende?
		//nein -> schritte 0-3 wiederholen
		//ja->1-3 wiederholen
		//das ganze solange bis der iterator auf die wurzel zeigt

	}

};

int main() {		//SPAETER IN EIGENE KLASSE AUSLAGERN
	typedef char key_type;           // string=basic_string<char>
	typedef string mapped_type;
	Trie<string, key_type>* t = new Trie<string, key_type>();
	basic_string<char> key("wir");
	key.push_back('\0');
	string s("we");
	const pair<const basic_string<char>, mapped_type> value = std::make_pair(
			key, s);
	t->insert(value);
	// typedef pair<const key_type, T> value_type;

	basic_string<char> key2("we");
	key2.push_back('\0');
	string s2("bla");
	const pair<const basic_string<char>, mapped_type> value2 = std::make_pair(
			key2, s2);
	t->insert(value2);
	t->print();
	for (auto it = t->begin(); it != t->end(); ++it) {           //
		cout << (*it).first << "" << (*it).second;
	}
	return 0;
}

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
