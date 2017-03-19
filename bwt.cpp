#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string &text) {
    string result = "";
    std::vector<string> arr;
    arr.push_back(text);
    for (int i = 1; i < text.size(); i++) {
        arr.push_back(text.substr(text.size() - i) + text.substr(0, text.size() - i));
    }

    std::sort(arr.begin(), arr.end());

    for (auto &&x: arr) {
        result += x[x.size() - 1];
    }
    return result;
}

int main() {
    string text;
    cin >> text;
    std::cout << BWT(text) << "\n";
    return 0;
}