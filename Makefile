all: main.cpp trie.cpp trie.hpp
	g++ main.cpp -o tgf -O3 -flto --std=c++17
