#ifndef TRIE_HPP
#define TRIE_HPP

#include <vector>
#include <fstream>
#include <string>

#define BUFFER_SIZE 5'242'880

class Trie {
    struct Edge;

    struct Node {
        bool term = false;
        std::vector<Edge> edges;
    };
    struct Edge {
        char chr;
        Node *node;
    };

    Node* root;
    void insert(Node* node, const std::string_view &str);
    void list(Node* node, std::string &buffer, std::ofstream &stream, std::string path);

public:
    Trie() : root(new Node) {};
    void insert(const std::string_view &str);
    void list(std::ofstream &stream);
};

#endif // TRIE_HPP
