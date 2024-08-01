#include "trie.hpp"
#include <fstream>
#include <algorithm>

void Trie::insert(Node* node, const std::string_view &str) {
    if (str.length() == 0) {
        node->term = true;
        return;
    }

    const auto &edge = std::find_if(
        node->edges.begin(),
        node->edges.end(),
        [str](Edge& e){return e.chr == str[0];}
    );

    Node *next_node;
    if (edge != node->edges.end())
        next_node = edge->node;
    else {
        next_node = new Node;
        node->edges.push_back({str[0], next_node});
    }

    this->insert(next_node, str.substr(1));  
}

void Trie::insert(const std::string_view &str) {
    this->insert(this->root, str);
}

void Trie::list(Node* node,
                std::string &buffer,
                std::ofstream &stream,
                std::string path) {
    if (node->term) {
        if (buffer.length() + path.length() > BUFFER_SIZE) {
            stream << buffer;
            buffer.clear();
        }
        buffer += path + "\n";
    }

    for (const Edge& edge : node->edges)
        this->list(edge.node, buffer, stream, path + edge.chr);
}

void Trie::list(std::ofstream &stream) {
    std::string buffer;
    buffer.reserve(BUFFER_SIZE);
    this->list(this->root, buffer, stream, "");
    if (buffer.length() > 0) stream << buffer;
}
