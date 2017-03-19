#include <iostream>
#include <vector>

int fibonacci_sum_last_digit(long long n) {
    std::vector<long long> fib;
    fib.push_back(0L);
    fib.push_back(1L);
    long long i = 2;
    while (true) {
        long long c = ((fib[i - 1] % 10) + (fib[i - 2] % 10)) % 10;
        if (fib[i - 1] == 1 && c == 0) break;
        else fib.push_back(c);
        i++;
    }
    return (fib[n % fib.size()] - 1 + 10) % 10;
}




int main() {
    long long n;
    std::cin >> n;
    long long c = fibonacci_sum_last_digit(n + 2);
    std::cout << c << '\n';
}
