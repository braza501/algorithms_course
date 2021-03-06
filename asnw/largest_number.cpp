#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

bool comp(const string &a, const string &b) {
    if (a.length() == b.length()) return a > b;
    string one = a + b;
    string two = b + a;
    if (one > two) {
        return true;
    } else {
        return false;
    }
}

string largest_number(vector<string> a) {

    std::sort(a.begin(), a.end(), comp);
    std::stringstream ret;
    for (size_t i = 0; i < a.size(); i++) {
        ret << a[i];
    }
    string result;
    ret >> result;
    return result;
}

int main() {
    int n;
    std::cin >> n;
    vector<string> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::cout << largest_number(a);

}
