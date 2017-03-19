#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.


vector<int> sort_chars(const string &s) {
    std::map<char, int> pos;
    pos['$'] = 0;
    pos['A'] = 1;
    pos['C'] = 2;
    pos['G'] = 3;
    pos['T'] = 4;
    vector<int> order(s.size());
    vector<int> count(5, 0);
    for (int i = 0; i < s.size(); i++) {
        count[pos[s[i]]]++;
    }
    for (int j = 1; j < count.size(); j++) {
        count[j] += count[j - 1];
    }
    for (int i = s.size() - 1; i >= 0; i--) {
        int c = pos[s[i]];
        count[c]--;
        order[count[c]] = i;
    }
    return order;
}

vector<int> compute_char_classes(string s, const vector<int> &order) {
    vector<int> clas(s.size());
    clas[order[0]] = 0;
    for (int i = 1; i < s.size(); i++) {
        if (s[order[i]] != s[order[i - 1]]) {
            clas[order[i]] = clas[order[i - 1]] + 1;
        } else {
            clas[order[i]] = clas[order[i - 1]];
        }
    }
    return clas;
}

vector<int> sort_doubled(const string &S, int L, const vector<int> &order, const vector<int> &clas) {
    vector<int> count(S.size(), 0);
    vector<int> newOrder(S.size());
    for (int i = 0; i < S.size(); i++) {
        count[clas[i]]++;
    }
    for (int j = 1; j < S.size(); j++) {
        count[j] += count[j - 1];
    }
    for (int i = S.size() - 1; i >= 0; i--) {
        int start = (order[i] - L + S.size()) % S.size();
        int cl = clas[start];
        count[cl]--;
        newOrder[count[cl]] = start;
    }
    return newOrder;
}

vector<int> updated_class(vector<int> newOrder, const vector<int>& clas, int L) {
    int n = newOrder.size();
    vector<int> newClas(n);
    newClas[newOrder[0]] = 0;
    for (int i = 1; i < n; i++) {
        int cur = newOrder[i], prev = newOrder[i - 1];
        int mid = (cur + L) % n, midPrev = (prev + L) % n;
        if (clas[cur] != clas[prev] || clas[mid] != clas[midPrev]) {
            newClas[cur] = newClas[prev] + 1;
        } else {
            newClas[cur] = newClas[prev];
        }
    }
    return newClas;
}

vector<int> BuildSuffixArray(const string &S) {
    vector<int> order = sort_chars(S);
    vector<int> clas = compute_char_classes(S, order);
    int L = 1;
    while (L < S.size()) {
        order = sort_doubled(S, L, order, clas);
        clas = updated_class(order, clas, L);
        L = 2 * L;
    }
    return order;
}

int main() {
    string text;
    cin >> text;
    vector<int> suffix_array = BuildSuffixArray(text);
    for (int i = 0; i < suffix_array.size(); ++i) {
        cout << suffix_array[i] << ' ';
    }
    cout << endl;
    return 0;
}
