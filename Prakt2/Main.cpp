#include "Trie.h"

int main() {
	typedef char key_type;           // string=basic_string<char>
	typedef string mapped_type;
	Trie<string, key_type>* t = new Trie<string, key_type>();
	basic_string<char> key("sind");
	key.push_back('\0');
	string s("are");
	const pair<const basic_string<char>, mapped_type> value = std::make_pair(
			key, s);
	t->insert(value);
	// typedef pair<const key_type, T> value_type;

	basic_string<char> key2("weiss");
	key2.push_back('\0');
	string s2("know");
	const pair<const basic_string<char>, mapped_type> value2 = std::make_pair(
			key2, s2);
	t->insert(value2);

	basic_string<char> key3("wer");
	key3.push_back('\0');
	string s3("who");
	const pair<const basic_string<char>, mapped_type> value3 = std::make_pair(
			key3, s3);
	t->insert(value3);

	basic_string<char> key4("wir");
	key4.push_back('\0');
	string s4("we");
	const pair<const basic_string<char>, mapped_type> value4 = std::make_pair(
			key4, s4);
	t->insert(value4);

	basic_string<char> key5("wird");
	key5.push_back('\0');
	string s5("will");
	const pair<const basic_string<char>, mapped_type> value5 = std::make_pair(
			key5, s5);
	t->insert(value5);

	basic_string<char> key6("wo");
	key6.push_back('\0');
	string s6("where");
	const pair<const basic_string<char>, mapped_type> value6 = std::make_pair(
			key6, s6);
	t->insert(value6);

	t->print();

//	auto it = t->begin();
//	(*it).print();
//	++it;
//	(*it).print();
//	++it;

	cout << "start iterator loop\n";
	for (auto it = t->begin(); it != t->end(); ++it) {           //
		(*it).second->printNode(0);
	}

	auto it = t->find(key);
	cout << "from main " << endl;
	(*it).second->printNode(0);
	auto it2 = t->find(key6);
	(*it2).second->printNode(0);

	basic_string<char> key7("we");
	key7.push_back('\0');
	if (t->find(key7) == t->end()){
		cout << "passt";
	}
	return 0;
}
