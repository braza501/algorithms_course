#include <iostream>
#include <vector>

int fibonacci_huge(long long n, long long m) {
    std::vector<long long> fib;
    fib.push_back(0L);
    fib.push_back(1L);
    long long i = 2;
    while (true) {
        long long c = ((fib[i - 1] % m) + (fib[i - 2] % m)) % m;
        if (fib[i - 1] == 1 && c == 0) break;
        else fib.push_back(c);
        i++;
    }
    return fib[n % fib.size()];
}


int main() {
    long long n, m;
    std::cin >> n >> m;
    long long c = fibonacci_huge(n, m);
    std::cout << c << '\n';
}
