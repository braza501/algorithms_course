#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <climits>
#include <cmath>
#include <cstdlib>


using std::vector;
using std::string;
using std::max;
using std::min;

long long perform_op(long long a, long long b, char op) {
    switch (op) {
        case '*':
            return a * b;
        case '+':
            return a + b;
        case '-':
            return a - b;
        default:
            throw "invalid";
    }
}

long long get_maximum_value(const string &exp) {
    long long n = (exp.size() + 1) / 2;
    long long m[n][n];
    long long M[n][n];

    for (long long i = 0; i < n; i++) {
        m[i][i] = strtol(exp.substr(2 * i, 1).c_str(), NULL, 10);
        M[i][i] = strtol(exp.substr(2 * i, 1).c_str(), NULL, 10);
    }

    for (long long s = 0; s < n - 1; s++) {
        for (long long i = 0; i < n - s - 1; i++) {
            long long j = i + s + 1;
            long long min_val = LLONG_MAX;
            long long max_val = LLONG_MIN;


            for (long long k = i; k < j; k++) {
                long long a = perform_op(m[i][k], m[k + 1][j], exp[2 * k + 1]);
                long long b = perform_op(m[i][k], M[k + 1][j], exp[2 * k + 1]);
                long long c = perform_op(M[i][k], m[k + 1][j], exp[2 * k + 1]);
                long long d = perform_op(M[i][k], M[k + 1][j], exp[2 * k + 1]);
                min_val = min(min_val, min(a, min(b, min(c, d))));
                max_val = max(max_val, max(a, max(b, max(c, d))));
            }
            m[i][j] = min_val;
            M[i][j] = max_val;
        }
    }

    return M[0][n - 1];
}

int main() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
}