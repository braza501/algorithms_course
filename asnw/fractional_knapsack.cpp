#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using std::vector;

bool weight_per_unit(const std::pair<int, int> &x, const std::pair<int, int> &y) {
    double one = (double) x.second / x.first;
    double two = (double) y.second / y.first;
    return one > two;
}

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
    double value = 0.0;
    std::vector<std::pair<int, int> > items;
    assert(weights.size() == values.size());
    size_t size = weights.size();
    for (int i = 0; i < size; i++) {
        items.push_back(std::make_pair(weights[i], values[i]));
    }
    assert(size == items.size());
    std::sort(items.begin(), items.end(), weight_per_unit);
    for (int i = 0; i < items.size(); i++) {

        if (items[i].first <= capacity) {
            capacity -= items[i].first;
            value += (double)items[i].second;
        } else {
            value += (double)capacity * ((double) items[i].second / items[i].first);
            break;
        }
    }
    return value;
}

int main() {
    int n;
    int capacity;
    std::cin >> n >> capacity;
    vector<int> values(n);
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        std::cin >> values[i] >> weights[i];
    }

    double optimal_value = get_optimal_value(capacity, weights, values);

    std::cout.precision(10);
    std::cout << optimal_value << std::endl;
    return 0;
}
