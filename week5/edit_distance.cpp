#include <vector>
#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include <ctime>

int edit_distance(const std::string &str1, const std::string &str2) {
    int m = str1.length(), n = str2.length();
    int a[m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        a[i][0] = i;
    }
    for (int i = 0; i <= n; i++) {
        a[0][i] = i;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {

            if (str1[i - 1] == str2[j - 1])
                a[i][j] = a[i - 1][j - 1];
            else
                a[i][j] = 1 + std::min(a[i][j - 1], std::min(a[i - 1][j], a[i - 1][j - 1]));
        }
    }

    return a[m][n];
}

int main() {
    std::string str1;
    std::string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
    return 0;
}
