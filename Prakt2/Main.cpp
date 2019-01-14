#include "Trie.h"
int main() {
	typedef char key_type;           // string=basic_string<char>
	typedef string mapped_type;
	Trie<string, key_type>* t = new Trie<string, key_type>();
	int choice;
	bool goOn = true;
	while (goOn) {
		cout << "**MAIN MENU**\n\n";
		cout << " 1 - Instantiate a default trie\n";
		cout << " 2 - Insert\n";
		cout << " 3 - Erase\n";
		cout << " 4 - Clear\n";
		cout << " 5 - Lower Bound\n";
		cout << " 6 - Upper Bound\n";
		cout << " 7 - Find\n";
		cout << " 8 - Print\n";
		cout << " Enter your choice and press return: ";

		cin >> choice;

		switch (choice) {
		case 1: {
			cout << "\n\n**INSTANTIATE A DEFAULT TRIE**\n\n";
			basic_string<char> key("sind");
			key.push_back('\0');
			string s("are");
			const pair<const basic_string<char>, mapped_type> value =
					std::make_pair(key, s);
			t->insert(value);

			basic_string<char> key2("weiss");
			key2.push_back('\0');
			string s2("know");
			const pair<const basic_string<char>, mapped_type> value2 =
					std::make_pair(key2, s2);
			t->insert(value2);

			basic_string<char> key3("wer");
			key3.push_back('\0');
			string s3("who");
			const pair<const basic_string<char>, mapped_type> value3 =
					std::make_pair(key3, s3);
			t->insert(value3);

			basic_string<char> key4("wir");
			key4.push_back('\0');
			string s4("we");
			const pair<const basic_string<char>, mapped_type> value4 =
					std::make_pair(key4, s4);
			t->insert(value4);

			basic_string<char> key5("wird");
			key5.push_back('\0');
			string s5("will");
			const pair<const basic_string<char>, mapped_type> value5 =
					std::make_pair(key5, s5);
			t->insert(value5);

			basic_string<char> key6("wo");
			key6.push_back('\0');
			string s6("where");
			const pair<const basic_string<char>, mapped_type> value6 =
					std::make_pair(key6, s6);
			t->insert(value6);
			cout << "\n\n**A DEFAULT TRIE INSTANTIATED**\n\n";
			break;
		}
		case 2: {
			// insert
			cout << "\n\n**INSERT A VALUE**\n\n";
			cout << " Enter a key and press return: ";
			basic_string<char> key("");
			cin >> key;
			key.push_back('\0');
			string s("");
			cout << " Enter a value and press return: ";
			cin >> s;
			const pair<const basic_string<char>, mapped_type> value =
					std::make_pair(key, s);
			t->insert(value);
			cout << "\n\n**VALUE INSERTED**\n\n";
			break;
		}
		case 3: {
			// erase
			cout << "\n\n**ERASE A VALUE**\n\n";
			cout << " Enter a key and press return: ";
			basic_string<char> key("");
			cin >> key;
			key.push_back('\0');
			string s("");
			t->erase(key);
			cout << "\n\n**VALUE ERASED**\n\n";
			break;
		}
		case 4: {
			// clear
			cout << "\n\n**CLEAR TRIE**\n\n";
			t->clear();
			cout << "\n\n**TRIE CLEARED**\n\n";
			break;
		}
		case 5: {
			// lbound
			cout << "\n\n**LOWER BOUND**\n\n";
			cout << " Enter a key and press return: ";
			basic_string<char> key("");
			cin >> key;
			key.push_back('\0');
			string s("");
			auto it = t->lower_bound(key);
			if (it == t->end()) {
				cout << "\n\n**ELEMENT NOT FOUND**\n\n";
			} else {
				cout << "\n\n**LOWER BOUND ELEMENT:**\n\n";
				(*it).second->printNode(0);
			}
			break;
		}
		case 6: {
			// ubound
			cout << "\n\n**UPPER BOUND**\n\n";
			cout << " Enter a key and press return: ";
			basic_string<char> key("");
			cin >> key;
			key.push_back('\0');
			string s("");
			auto it = t->upper_bound(key);
			if (it == t->end()) {
				cout << "\n\n**ELEMENT NOT FOUND**\n\n";
			} else {
				cout << "\n\n**UPPER BOUND ELEMENT:**\n\n";
				(*it).second->printNode(0);
			}
			break;
		}
		case 7: {
			// find
			cout << "\n\n**FIND A VALUE**\n\n";
			cout << " Enter a key and press return: ";
			basic_string<char> key("");
			cin >> key;
			key.push_back('\0');
			string s("");
			auto it = t->find(key);
			if (it == t->end()) {
				cout << "\n\n**VALUE NOT FOUND**\n\n";
			} else {
				cout << "\n\n**VALUE FOUND**\n\n";
				(*it).second->printNode(0);
			}
			break;
		}
		case 8: {
			t->print();
			break;
		}
		case 666:
			cout << "Ciao!";
			goOn = false;
			break;
		default:
			cout << "Not a Valid Choice. \n";
			goOn = true;
			break;
		}

	}


	return 0;
}
