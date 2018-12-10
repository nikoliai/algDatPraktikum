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
	InnerNode root; // attribut der klasse trie
public:
	typedef basic_string<E> key_type;           // string=basic_string<char>
	typedef pair<const key_type, T> value_type;
	typedef T mapped_type;

	class Node {
		//Node* parentNode_ptr;
		key_type key; //here: letter in a word
	public:
		virtual void print();
		Node(key_type key) { //Node* parentNode,
			//this->parentNode_ptr = parentNode;
			this->key = key;
		}
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
		LeafNode(Node* parentNode, T value, key_type key) :
				Node(parentNode, key) {
			this->my_value = value;
		}
		void print() {
			//;printet das gemappte value und den key
			//std::cout << this->my_value << std::endl; key drucken
			std::cout << this->my_value << std::endl;
		}
		void print() {
			Node* n = this;
			std::list<Node*> visited; //speichert alle buchstaben
			while (n->hasParent()) {
				visited.push_front(n);
				n = n->getParentNode();
			}
			typename std::list<Node*>::iterator it;
			int spaces = 0;
			for (it = visited.begin(); it != visited.end(); ++it) {
				for (int i = 0; i < spaces; ++i) {
					std::cout << ' ';
				}
				spaces += 2;
				std::cout << (*it)->getKey() << std::endl;
			}
			for (int i = 0; i < spaces; ++i) {
				std::cout << ' ';
			}

			std::cout << this->my_value << std::endl;
		}
	};

	class InnerNode: Node {
	private:
		std::list<Node*> children;//Stattedssen map E-Typ-pointer
		void print() {
			// inneren knoten erstellen
		}
	public:
		InnerNode(Node* parentNode, std::list<Node*> children, key_type key) :
				Node(parentNode, key) {
			this->children = children;
		}

		void addChild(Node* child) {
			this->children.push_back(child);
			this->children.sort();
		}

	};

	// „...“ im folgenden typedef: keine C/C++ Ellipse, sondern von Ihnen
	// - am besten als innere Klasse - zu entwickeln…
	//typedef ... iterator;
//	  bool empty() const;


	void insert(const value_type& value);// rekursiv: vom ende her anfangen,
	//knoten erstellen,pointer setzen, dann pointer weitergeben(?); zwischendurch überprüfen:
	//1) ob der node schon existiert, also ob man verzweigen muss
	void print();//wir gehen alle knoten durch und schauen, wie denau das geprintet werden soll.



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

#endif /* TRIE_H_ */
