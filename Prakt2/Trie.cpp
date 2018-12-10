/*
 * Trie.cpp
 *
 *  Created on: 09.12.2018
 *      Author: Olenka
 */

#include "Trie.h"
int main() {
	Trie<int>::Node* parentNode_ptr = NULL;
	std::list<Trie<int>::Node*> initList = { };
	basic_string<char> letter;
	Trie<int>::InnerNode rootNode(parentNode_ptr, initList, letter);

	parentNode_ptr = (Trie<int>::Node*) &rootNode;
	initList = { };
	letter = 'w';
	Trie<int>::InnerNode wNode(parentNode_ptr, initList, letter);
	rootNode.addChild((Trie<int>::Node*)&wNode);

	parentNode_ptr = (Trie<int>::Node*) &wNode;
	initList = { };
	letter = 'i';
	Trie<int>::InnerNode iNode(parentNode_ptr, initList, letter);
	wNode.addChild((Trie<int>::Node*)&iNode);

	parentNode_ptr = (Trie<int>::Node*) &iNode;
	initList = { };
	letter = 'r';
	Trie<int>::InnerNode rNode(parentNode_ptr, initList, letter);
	iNode.addChild((Trie<int>::Node*)&rNode);

	parentNode_ptr = (Trie<int>::Node*) &rNode;
	initList = { };
	letter = '\0';
	Trie<int>::InnerNode terminateNode(parentNode_ptr, initList, letter);
	rNode.addChild((Trie<int>::Node*)&terminateNode);

	parentNode_ptr = (Trie<int>::Node*) &terminateNode;
	initList = { };
	int word = 666;
	letter = '\0';
	Trie<int>::LeafNode wordNode(parentNode_ptr, word, letter);
	rNode.addChild((Trie<int>::Node*)&terminateNode);

	wordNode.print();
//	Trie:: InnerNode i;
//		s.parentNode_ptr* = s;
//
//	Trie:: NodeLeaf leafSind;

}

