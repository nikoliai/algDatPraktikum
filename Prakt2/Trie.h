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

#ifndef TRIE_H_
#define TRIE_H_

using namespace std;

template<class T, class E = char>
class Trie {

private:
	typename Trie<T>::InnerNode root; // attribut der klasse trie
public:
	typedef basic_string<E> key_type;           // string=basic_string<char>
	typedef pair<const key_type, T> value_type;
	typedef T mapped_type;

	int mainFun();

	class Node {
		//Node* parentNode_ptr;
		key_type key; //here: letter in a word
	public:
		virtual void print();
		Node(key_type key) { //Node* parentNode,
			//this->parentNode_ptr = parentNode;
			this->key = key;
		}
		virtual bool isInnerNode();
		~Node() {
		}
		;
//		Node* getParentNode() {
//			return this->parentNode_ptr;
//		}
//		bool hasParent() {
//			return parentNode_ptr != NULL;
//		}
		key_type getKey() {
			return key;
		}
	};

	class LeafNode: Node {
		typedef T mapped_type;

	private:
		mapped_type my_value;

	public:
		LeafNode(T value, key_type key) :
				Node(key) {
			this->my_value = value;
		}

		void print() {
			//;printet das gemappte value und den key
			//std::cout << this->my_value << std::endl; key drucken
			std::cout << this->getKey() << ":" << this->my_value << std::endl;
		}
		bool  isInnerNode() {
				return false;
			}


	};

	class InnerNode: Node {
	private:
		std::map<E, Node*> childrenMap;

		void print() {
			cout << this->getKey();
		}

		bool  isInnerNode() {
			return true;
		}
	public:
		InnerNode(std::map<E, Node*> children, key_type key) :
				Node(key) {
			this->childrenMap = children;
		}

		std::map<E, Node*> getChildrenMap() {
			return childrenMap;
		}

	};

	// „...“ im folgenden typedef: keine C/C++ Ellipse, sondern von Ihnen
	// - am besten als innere Klasse - zu entwickeln…
	//typedef ... iterator;
//	  bool empty() const;

	void insert(const value_type& value) {
		key_type key = value.first;
		T data = value.second;
		const char* letter = key.c_str();
		insertNode(letter, root, value);
		// rekursiv: vom ende her anfangen,
	}
	;

	void insertNode(char* nextChar, InnerNode node, T val) {
		node.print();
		Node nextNode;
		if (nextChar != NULL) {
			if (node.getChildrenMap().find(*nextChar)
					!= node.getChildrenMap().end()) {
				//letter exists in the map
				nextNode = node.getChildrenMap().find(*nextChar);
			} else {
				//letter doesnt exist in the map, need to create
				std::map<E, Node*> map;
				key_type key;
				nextNode = new InnerNode(map, key);
				map.insert(*nextChar, &nextNode);
			}
			insertNode(nextChar + 1, nextNode);
		} else {
			nextNode = new LeafNode(val, '\0');
			node.getChildrenMap().insert('\0', &nextNode);
			node.print();
		}
	}

	//knoten erstellen,pointer setzen, dann pointer weitergeben(?); zwischendurch überprüfen:
	//1) ob der node schon existiert, also ob man verzweigen muss
	void print(Node* node) {
		node->print();
	if (isInnerNode()){
		std::map<E, Node*> children = node.getChildrenMap();
		if (children == NULL) {
			return;
		}
			else{
			for (auto i = children.begin(); i != children.end();i++	) {
					 print (i->first );

				}
			}
		}

		//wir gehen alle knoten durch und schauen, wie denau das geprintet werden soll.
	}
	;

//	  void erase(const key_type& value);
//	  void clear();  // erase all
//iterator lower_bound(const key_type& testElement);  // first element >= testElement
//iterator upper_bound(const key_type& testElement);  // first element  >  testElement
//	  iterator find(const key_type& testElement);    // first element == testElement
//	  iterator begin();  // returns end() if not found
//	  iterator end();
//

	Trie() {
	}
	;
	virtual ~Trie() {
	}
	;

};

int main() {
	typedef basic_string<char> key_type;           // string=basic_string<char>
	typedef string mapped_type;
//	Trie<string> t;
	pair<key_type, mapped_type> value("w", "we");
//	t.insert(value);
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
