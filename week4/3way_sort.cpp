#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

int partition2(vector<int> &a, int l, int r) {

}

void randomized_quick_sort(vector<int> &a, int l, int r) {
    if (l >= r) {
        return;
    }

    int k = l + rand() % (r - l + 1);
    swap(a[l], a[k]);

    int l_iterator = l, r_iterator = r;
    int pivot = a[l];
    int i = l;
    while (i <= r_iterator) {
        if (a[i] < pivot) {
            std::swap(a[l_iterator], a[i]);
            l_iterator++;
            i++;
        } else if (a[i] > pivot) {
            std::swap(a[i], a[r_iterator]);
            r_iterator--;
        } else i++;
    }

    randomized_quick_sort(a, l, l_iterator - 1);
    randomized_quick_sort(a, r_iterator + 1, r);
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    randomized_quick_sort(a, 0, a.size() - 1);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
}
