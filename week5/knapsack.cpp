#include <vector>
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>

int optimal_weight(int W, const std::vector<int> &weights) {
    int size = weights.size();

    std::vector<std::vector<int>> c(size + 1);
    for (int i = 0; i < c.size(); i++) {
        c[i].resize(W + 1);
    }
    for (int i = 0; i <= size; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                c[i][w] = 0;
            else if (weights[i - 1] <= w)
                c[i][w] = std::max(weights[i - 1] + c[i - 1][w - weights[i - 1]], c[i - 1][w]);
            else
                c[i][w] = c[i - 1][w];
        }
    }

    return c[size][W];
}

int main() {
    int n, W;
    srand(time(NULL));

    std::cin >> W;
    std::cin >> n;

    std::vector<int> w(n);
    for (int i = 0; i < n; i++) {
         std::cin >> w[i];
    }
    std::cout << optimal_weight(W, w) << '\n';


}