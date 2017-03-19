#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector;

int get_majority_element(vector<int> &a) {
    std::unordered_map<int, int> elements;
    for (int var: a) {
        elements[var]++;
    }
    double threshold = (double) a.size() / 2.0;
    for (auto &&var: elements) {
        if ((double) var.second > threshold) {
            return 1;
        }
    }
    return -1;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    std::cout << (get_majority_element(a) != -1) << '\n';
}
