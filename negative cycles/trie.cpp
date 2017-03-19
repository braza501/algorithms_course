#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>
#include <sstream>

using std::map;
using std::vector;
using std::string;


struct Node {
    static int numNodes;
    char letter = 'B';
    int num = -1;
    Node *parent = nullptr;
    Node *children[4] = {nullptr, nullptr, nullptr, nullptr};

    Node(char l, Node *p) {
        letter = l;
        parent = p;
        num = numNodes++;
    }
};

int Node::numNodes = 0;

struct Trie {
    Node *root;
    vector<Node *> nodes;
    int numWords;

    Trie() {
        root = new Node('\0', nullptr);
        nodes.push_back(root);
    }

    void add(string word) {
        Node *curr = root;
        for (int i = 0; i < word.length(); ++i) {
            char let = word[i];
            int c;
            switch (let) {
                case 'A':
                    c = 0;
                    break;
                case 'C':
                    c = 1;
                    break;
                case 'G':
                    c = 2;
                    break;
                case 'T':
                    c = 3;
                    break;
                default:
                    throw "wrong!";
            }
            if (curr->children[c] == nullptr) {
                curr->children[c] = new Node(let, curr);
                nodes.push_back(curr->children[c]);
            }
            curr = curr->children[c];
        }
    }

    vector<std::pair<int,string>> edge() {
        vector<std::pair<int,string>> out(nodes.size() - 1);
        for (int i = 0; i < out.size(); ++i) {
            Node *curr = nodes[i + 1];
            std::ostringstream convert;
            convert << curr->parent->num << "->" << curr->num << ":" << curr->letter;
            out[i] = std::make_pair(curr->parent->num,convert.str());
        }
        std::sort(out.begin(), out.end());
        return out;
    }
};


vector<std::pair<int,string>> build_trie(vector<string> &patterns) {
    Trie trie = Trie();
    for (int i = 0; i < patterns.size(); ++i) {
        trie.add(patterns[i]);
    }
    return trie.edge();
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<std::string> patterns;
    for (size_t i = 0; i < n; i++) {
        string s;
        std::cin >> s;
        patterns.push_back(s);
    }

    vector<std::pair<int,string>> t = build_trie(patterns);
    for (int i = 0; i < t.size(); ++i) {
        std::cout << t[i].second << "\n";
    }


    return 0;
}