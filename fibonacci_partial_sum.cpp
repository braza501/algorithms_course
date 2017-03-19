#include <iostream>
#include <vector>

using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    if (to <= 1)
        return to;

    long long previous = 0;
    long long current = 1;

    for (long long i = 0; i < from - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    long long sum = current;

    for (long long i = 0; i < to - from; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

long long fibonacci_sum_last_digit(long long n) {
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

long long get_fibonacci_partial_sum_fast(long long from, long long to) {
    if (to <= 1)
        return to;
    if (from <= 1) {
        return fibonacci_sum_last_digit(to + 2);
    }

    long long one = fibonacci_sum_last_digit(to + 2);
    long long two = fibonacci_sum_last_digit(from + 2 - 1);
    return (one - two + 10) % 10;
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
