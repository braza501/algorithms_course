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
    int numChildren = 0;
    bool is_pattern = false;
    Node *children[4] = {nullptr, nullptr, nullptr, nullptr};

    Node(char l) {
        numChildren = 0;
    }
};

struct Trie {
    Node *root;

    Trie() {
        root = new Node('\0');
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
                curr->children[c] = new Node(let);
                ++(curr->numChildren);
            }
            curr = curr->children[c];
        }
        curr->is_pattern = true;
    }

};


Trie build_trie(vector<string> &patterns) {
    Trie trie = Trie();
    for (int i = 0; i < patterns.size(); ++i) {
        trie.add(patterns[i]);
    }
    return trie;
}

vector<int> solve(string text, vector<string> patterns) {
    Trie trie = build_trie(patterns);
    vector<int> ans;
    for (int start = 0; start < text.length(); ++start) {
        Node *currNode = trie.root;
        bool added = false;
        for (int i = start; i < text.length(); ++i) {
            int letter;
            switch (text[i]) {
                case 'A':
                    letter = 0;
                    break;
                case 'C':
                    letter = 1;
                    break;
                case 'G':
                    letter = 2;
                    break;
                case 'T':
                    letter = 3;
                    break;
                default:
                    throw "fault";
            }
            if (currNode->numChildren == 0) {
                ans.push_back(start);
                added = true;
                break;
            } else if (currNode->children[letter] == nullptr) {
                break;
            } else if (currNode->children[letter]->is_pattern) {
                ans.push_back(start);
                added = true;
                break;
            } else {
                currNode = currNode->children[letter];
            }
        }
        if (currNode != trie.root && !added && currNode->numChildren == 0) {
            ans.push_back(start);
        }
    }

    return ans;
}

int main(void) {
    string t;
    std::cin >> t;

    int n;
    std::cin >> n;

    vector<string> patterns(n);
    for (int i = 0; i < n; i++) {
        std::cin >> patterns[i];
    }

    vector<int> ans = solve(t, patterns);

    for (int i = 0; i < (int) ans.size(); i++) {
        std::cout << ans[i];
        if (i + 1 < (int) ans.size()) {
            std::cout << " ";
        } else {
            std::cout << std::endl;
        }
    }

    return 0;
}
