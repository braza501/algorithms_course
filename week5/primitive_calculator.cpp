#include <vector>
#include <iostream>
#include <list>

std::list<int> optimal_sequence(int number) {
    std::vector<int> c(number + 1);
    std::vector<int> path(number + 1);

    for (int i = 2; i <= number; i++) {
        c[i] = c[i - 1] + 1;
        path[i] = i - 1;
        if (i % 3 == 0) {
            if (c[i / 3] < c[i]) {
                c[i] = c[i / 3] + 1;
                path[i] = i / 3;
            }
        }
        if (i % 2 == 0) {
            if (c[i / 2] < c[i]) {
                c[i] = c[i / 2] + 1;
                path[i] = i / 2;
            }
        }
    }
    std::list<int> sequence;
    for (int i = number; i != 0; i = path[i]) {
        sequence.push_front(i);
    }
    return sequence;
}

int main() {
    int n;
    std::cin >> n;
    std::list<int> sequence = optimal_sequence(n);
    std::cout << sequence.size() - 1 << std::endl;
    for (auto &&x: sequence) {
        std::cout << x << " ";
    }
}

