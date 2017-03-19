#include <iostream>
#include <vector>

using std::vector;

long long merge(vector<int> &a, vector<int> &b, int left, int ave, int right) {
    long long inv = 0;
    for (int k = left; k <= right; k++) {
        b[k] = a[k];
    }

    int i = left, j = ave + 1;
    for (int k = left; k <= right; k++) {
        if (i > ave) a[k] = b[j++];
        else if (j > right) a[k] = b[i++];
        else if (b[i] <= b[j]) {
            a[k] = b[i++];
        } else {
            inv += ave - i + 1;
            a[k] = b[j++];
        }
    }
    return inv;
}

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
    if (right <= left) return 0;
    long long number_of_inversions = 0;
    size_t ave = left + (right - left) / 2;
    number_of_inversions += get_number_of_inversions(a, b, left, ave);
    number_of_inversions += get_number_of_inversions(a, b, ave + 1, right);
    number_of_inversions += merge(a, b, left, ave, right);
    return number_of_inversions;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    vector<int> b(a.size());
    std::cout << get_number_of_inversions(a, b, 0, a.size() - 1) << '\n';
}
