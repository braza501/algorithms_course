#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where
// the pattern starts in the text.

vector<int> prefix_func(const string &pattern) {
    vector<int> s(pattern.size());
    s[0] = 0;
    int border = 0;
    for (int i = 1; i < pattern.size(); i++) {
        while ((border > 0) && !(pattern[i] == pattern[border])) {
            border = s[border - 1];
        }
        if (pattern[i] == pattern[border]) {
            border++;
        } else {
            border = 0;
        }
        s[i] = border;
    }
    return s;
}

vector<int> find_pattern(const string &pattern, const string &text) {
    vector<int> result;
    string s = pattern + '$' + text;
    vector<int> prefixes = prefix_func(s);
    for(int i = pattern.size() + 1; i < s.size(); i++){
            if(prefixes[i] == pattern.size()){
                result.push_back(i - 2 * pattern.size());
            }
    }
    return result;
}

int main() {
    string pattern, text;
    cin >> pattern;
    cin >> text;
    vector<int> result = find_pattern(pattern, text);
    for (int i = 0; i < result.size(); ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");
    return 0;
}
