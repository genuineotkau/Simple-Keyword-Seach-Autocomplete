
#include <iostream>
#include <string>

using namespace std;

class Input_Processing {
private:
	string command = "";
	string parameter = "";


public:

	void Process_cin(string input);
	string get_command();
	string get_parameter();
};

class illegal_exception {
private:
	string error_text = "illegal argument";
public:
	void print_msg() {
		cout << error_text << endl;
	}

};

class Node {
	friend class Trie;
private:

	Node* children[26] = {};
	Node* parent = nullptr;
	bool is_terminal = false;
};

class Trie {
private:

	Node* root = nullptr;
	Node* temp = nullptr;
	unsigned int size = 0;
	bool first_delete_loop = true;
	string word_collector = "";

	int char_to_int(char single_str);
	bool recursive_insert(string word, unsigned int position);
	bool recursive_delete(string word, Node* erase_node);
	void collect_to_print(Node* start_node, string prefix);
	bool empty(Node* cheking_node);


public:
	Trie();

	Node* get_root();

	void Inser_Word(string word);

	bool Erase_Word(string word);

	void print(Node* start_node, string prefix);

	void search(string word);

	void autocomplete_words(string word);

	void clear();

	void print_size();

	void print_empty();

	~Trie();
};