#
all: triedriver

# list the test program all classes (cpp files)
#  cpp files must use #include , to include *.h or *.hpp files

triedriver: trietest.cpp trie.cpp trie.h
	g++ -std=c++11 -o triedriver trie.h trie.cpp trietest.cpp
# List all the executables under 'all:'
clean:
	rm triedriver