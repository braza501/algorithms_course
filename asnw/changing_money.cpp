#include <iostream>
#include <cassert>

int get_change(int m) {
    int count = 0;
    int temp;
    if (m >= 10) {
        temp = m / 10;
        count += temp;
        m -= (temp * 10);
    }
    if (m >= 5) {
        temp = m / 5;
        count += temp;
        m -= temp * 5;
    }
    if (m >= 1) {
        temp = m / 1;
        count += temp;
        m -= temp * 1;
    }
    assert(m == 0);
    return count;
}

int main() {
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}
