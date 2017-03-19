#include <iostream>
#include <vector>

using std::vector;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
    int n = a.size(), m = b.size(), k = c.size();
    int A[n + 1][m + 1][k + 1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int t = 0; t <= k; t++) {
                if (i == 0 || j == 0 || t == 0)
                    A[i][j][t] = 0;

                else if (a[i - 1] == b[j - 1] && b[j - 1] == c[t - 1])
                    A[i][j][t] = A[i - 1][j - 1][t - 1] + 1;

                else {
                    A[i][j][t] = std::max(A[i - 1][j][t], std::max(A[i][j - 1][t], A[i][j][t - 1]));

                }
            }
        }
    }
    return A[n][m][k];
}

int main() {
    size_t an;
    std::cin >> an;
    vector<int> a(an);
    for (size_t i = 0; i < an; i++) {
        std::cin >> a[i];
    }
    size_t bn;
    std::cin >> bn;
    vector<int> b(bn);
    for (size_t i = 0; i < bn; i++) {
        std::cin >> b[i];
    }
    size_t cn;
    std::cin >> cn;
    vector<int> c(cn);
    for (size_t i = 0; i < cn; i++) {
        std::cin >> c[i];
    }
    std::cout << lcs3(a, b, c) << std::endl;
}
