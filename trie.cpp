#include <iostream>
#include <string>
#include "trie.h"

using namespace std;

void Input_Processing::Process_cin(string input) {
	string temp1;
	string::size_type pos = input.find(" "); //First blank space


	if (string::npos == pos) {
		command = input;
	}
	else {
		temp1 = input;
		parameter = temp1.substr(pos + 1); //Stuff after first whitespace.
		command = temp1.erase(pos); //The command is 1 position before the 1st whitespace
	}

	if (command.back() == ' ') {
		command.pop_back();
	}

	if (parameter.back() == ' ') {
		parameter.pop_back();
	}

	//cout << "command: " << command << endl;
	//cout << "parameter: " << parameter << endl;


}

string Input_Processing::get_command() {
	//cout << "command: "<<command << endl;
	return command;
}

string Input_Processing::get_parameter() {
	//cout << "parameter: " << parameter << endl;
	return parameter;
}



Trie::Trie() {
	root = new Node();
}

Trie::~Trie() {
	//Destroy everything in the object
	clear();
	delete temp;
	delete root;
}

Node* Trie::get_root() {
	return root;
}

void Trie::Inser_Word(string word) {

	//Input Checking
	try {

		for (unsigned int i = 0; i < word.size(); i++) {

			bool is_valid = false;

			//Check if each word is valid
			for (string iterator = "a"; iterator <= "z"; iterator[0] += 1) {
				if (word[i] == iterator[0]) {
					is_valid = true;
				}
			}

			if (is_valid == false) {
				throw illegal_exception();
			}
		}
	}
	catch (illegal_exception e) {
		e.print_msg();
		return;
	}


	temp = root;
	int insertion_success = recursive_insert(word, 0);
	temp = nullptr;

	if (insertion_success) {
		cout << "success" << endl;
		size += 1;
	}
	else {
		cout << "failure" << endl;
	}

}

bool Trie::recursive_insert(string word, unsigned int position) {
	string empty = "";
	Node* initialize = new Node();

	if (word[position] != empty[0]) {
		int node_num = char_to_int(word[position]);
		if (temp->children[node_num] == nullptr) {

			temp->children[node_num] = initialize;
			initialize->parent = temp;
			temp = temp->children[node_num];

			//deallocate the temporary initializer
			initialize = 0;
			delete initialize;

			if (word[position + 1] == empty[0]) {
				temp->is_terminal = true;
				return true;
			}
			return (recursive_insert(word, position + 1));
		}
		else {
			//deallocate the temporary initializer
			delete initialize;

			temp = temp->children[node_num];
			//If last node is located at terminal, there is a duplicate
			if (word[position + 1] == empty[0] && temp->is_terminal == true) {
				return false;
			}
			//If last node is part of other words but is not a terminal
			//it should be valid, and we make it a terminal
			else if (word[position + 1] == empty[0] && temp->is_terminal == false) {
				temp->is_terminal = true;
				return true;
			}
			return (recursive_insert(word, position + 1));
		}
	}

	//For debugging use, in normal running cases, the code won't reach here.
	initialize = 0;
	delete initialize;
	cout << "Something is wrong in recursive insertion." << endl;
	return false;

}

//This function is responsible for nevigating a pointer to the 
//last node of the corresponding word
bool Trie::Erase_Word(string word) {

	//Input Checking
	try {

		for (unsigned int i = 0; i < word.size(); i++) {

			bool is_valid = false;

			//Check if each word is valid
			for (string iterator = "a"; iterator <= "z"; iterator[0] += 1) {
				if (word[i] == iterator[0]) {
					is_valid = true;
				}
			}

			if (is_valid == false) {
				throw illegal_exception();
			}
		}
	}
	catch (illegal_exception e) {
		e.print_msg();
		return false;
	}

	Node* ending_node = root;

	for (unsigned int i = 0; i < word.size(); i++) {
		char letter = word[i];
		int position = char_to_int(letter);
		bool deletion_success;

		//If not at the end of the word
		//then it is impossible for the next corresponding
		//letter to be none

		if (ending_node->children[position] == nullptr) {
			//Deallocate temprary pointer
			ending_node = 0;
			delete ending_node;
			cout << "failure" << endl;
			return false;
		}
		//If next letter's position exists, move deeper
		ending_node = ending_node->children[position];

		//When we are at the last Node:
		if (i == (word.size() - 1)) {
			//The the code has moved to the last letter
			if (ending_node->is_terminal == false) {
				//Deallocate temprary pointer
				ending_node = 0;
				delete ending_node;
				cout << "failure" << endl;
				return false;
			}
			else {
				first_delete_loop = true;
				deletion_success = recursive_delete(word, ending_node);
				if (deletion_success) {
					size -= 1;
					return true;
				}
				else {
					cout << "somethig is wrong, check code" << endl;
				}
				return false;
			}
		}

	}
}

bool Trie::recursive_delete(string word, Node* erase_node) {
	bool is_empty = empty(erase_node);

	if (is_empty) {
		if (erase_node->parent == nullptr) {
			//we are at root now, nothing more to do
			return true;
		}

		if (first_delete_loop == false && erase_node->is_terminal == true) {
			return true;
		}

		//If a node is deletable, erase it and go to above Node
		Node* to_be_delete = nullptr;
		to_be_delete = erase_node;
		erase_node = erase_node->parent;

		//Break the child node with its parent node
		for (int i = 0; i <= 25; i++) {
			if (erase_node->children[i] == to_be_delete) {
				erase_node->children[i] = nullptr;
			}
		}
		to_be_delete->parent = nullptr;
		delete to_be_delete;
		first_delete_loop = false;
		return recursive_delete(word, erase_node);
	}
	else {
		//If a node is not deletable,
		//only erase the terminal when it is first call
		//because Node on first call is the last letter
		if (first_delete_loop = true && erase_node->is_terminal == true)
			erase_node->is_terminal = false;
		return true;

	}

	cout << "The code shouldn't be here. Something is wrong." << endl;
	return false;

}

//Search is bascially cpoy pasting the
//first half Erase function
void Trie::search(string word) {
	try {

		for (unsigned int i = 0; i < word.size(); i++) {

			bool is_valid = false;

			//Check if each word is valid
			for (string iterator = "a"; iterator <= "z"; iterator[0] += 1) {
				if (word[i] == iterator[0]) {
					is_valid = true;
				}
			}

			if (is_valid == false) {
				throw illegal_exception();
			}
		}
	}
	catch (illegal_exception e) {
		e.print_msg();
		return;
	}

	Node* ending_node = root;
	for (unsigned int i = 0; i < word.size(); i++) {
		char letter = word[i];
		int position = char_to_int(letter);

		if (ending_node->children[position] == nullptr) {
			//Deallocate temprary pointer
			ending_node = 0;
			delete ending_node;
			cout << "not found" << endl;
			return;
		}
		//If next letter's position exists, move deeper
		ending_node = ending_node->children[position];

		//When we are at the last Node:

		if (i == (word.size() - 1)) {
			//The the code has moved to the last letter
			if (ending_node->is_terminal == false) {
				//Deallocate temprary pointer
				ending_node = 0;
				delete ending_node;
				cout << "not found" << endl;
				return;
			}
			else {
				cout << "found " << word << endl;
				return;
			}
		}

	}
}

void Trie::clear() {
	word_collector = "";

	collect_to_print(root, "");

	string::size_type length_mark = word_collector.find(" ");

	string after_space = "";
	string before_space = "";
	string container = word_collector;

	if (length_mark != string::npos) {
		after_space = word_collector.substr(length_mark + 1);
		before_space = container.erase(length_mark);
	}

	//Using the word_collector and container
	//we can delete all the words in the trie one by one
	while (length_mark != string::npos) {
		Erase_Word(before_space);
		length_mark = after_space.find(" ");
		container = after_space;
		after_space = after_space.substr(length_mark + 1);
		if (container == "" || container == " ") {
			break;
		}
		before_space = container.erase(length_mark);
	}

}

void Trie::autocomplete_words(string word) {
	//Remove the * at the back
	word.pop_back();
	if (word == "") {
		print(root, "");
	}

	for (unsigned int i = 0; i < word.size(); i++) {
		Node* ending_node = root;
		for (unsigned int i = 0; i < word.size(); i++) {
			char letter = word[i];
			int position = char_to_int(letter);

			if (ending_node->children[position] == nullptr) {
				//Deallocate temprary pointer
				ending_node = 0;
				delete ending_node;
				return;
			}
			//If next letter's position exists, move deeper
			ending_node = ending_node->children[position];



			if (i == (word.size() - 1)) {

				//When we are at the last Node:
				//The the code has moved to the last letter

				word_collector = "";
				collect_to_print(ending_node, word);

				if (word_collector != " ") {

					word_collector.pop_back();

					cout << word_collector << endl;

					word_collector = "";

					return;
				}



			}
		}
	}
}

int Trie::char_to_int(char single_str) {

	int counter = 0;

	//Check if each word is valid
	for (string iterator = "a"; iterator <= "z"; iterator[0] += 1) {
		if (single_str == iterator[0]) {
			return counter;
		}
		counter++;
	}

	cout << "Something is wrong, need debugging!!!!!!!!!!" << endl;
	return 0;
}

bool Trie::empty(Node* checking_node) {

	bool is_empty = true;
	for (int i = 0; i <= 25; i++) {

		if (checking_node->children[i] != nullptr) {
			is_empty = false;
		}
	}

	return is_empty;

}

void Trie::print(Node* start_node, string prefix) {

	word_collector = "";

	collect_to_print(start_node, prefix);

	//No matter what, the collector will not be ""
	//Refer to word_collector = word_collector + prefix + " ";
	if (word_collector != " ") {

		word_collector.pop_back();

		cout << word_collector << endl;
	}
}

void Trie::collect_to_print(Node* start_node, string prefix) {
	if (empty(start_node)) {
		word_collector = word_collector + prefix + " ";
		return;
	}

	if (start_node->is_terminal == true) {
		word_collector = word_collector + prefix + " ";
	}

	Node* deeper_node = nullptr;
	unsigned int count = 0;

	for (char i = 'a'; i <= 'z'; i++) {

		if (start_node->children[count] != nullptr) {
			deeper_node = start_node->children[count];
			prefix.push_back(i);
			collect_to_print(deeper_node, prefix);
			prefix.pop_back();
		}

		count++;
	}

	deeper_node = 0;
	delete deeper_node;
}

void Trie::print_size() {
	cout << "number of words is " << size << endl;
}

void Trie::print_empty() {
	cout << "empty " << empty(root) << endl;
}
