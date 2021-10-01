#include <iostream>
#include <string>
#include "trie.h"

using namespace std;

//Creating different respondes to each command
bool manipulation(Input_Processing& Inputs, Trie& trie) {
	string command = Inputs.get_command();
	string parameter = Inputs.get_parameter();

	if (command == "i") {
		trie.Inser_Word(parameter);
	}
	else if(command == "print"){
		trie.print(trie.get_root(),"");
	}
	else if (command == "e") {
		if (trie.Erase_Word(parameter)) {
			cout << "success" << endl;
		}
	}
	else if (command == "s") {
		trie.search(parameter);
	}
	else if (command == "autocomplete") {
		trie.autocomplete_words(parameter);
	}
	else if (command == "clear") {
		trie.clear();
		cout << "success" << endl;
	}
	else if (command == "size") {
		trie.print_size();
	}
	else if (command == "empty") {
		trie.print_empty();
	}
	else if (command == "exit") {
		return true;
	}

	return false;
}

int main() {
	string user_input;
	Input_Processing Inputs;
	Trie trie;

	while (true) {
		bool is_exit = false;
		getline(cin, user_input);
		Inputs.Process_cin(user_input);
		is_exit = manipulation(Inputs, trie);
		if (is_exit == true)
		{
			break;
		}
	}
	//Destructor will be automatically called at the end.
	return 0;
}

