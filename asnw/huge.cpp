#include <iostream>
#include <vector>

int get_fibonacci_last_digit_fast(int m) {
    std::vector<int> fib;
    fib.push_back(0);
    fib.push_back(1);
    int i = 2;
    while (true) {
        int c = (fib[i - 1] + fib[i - 2]) % m;
        if (fib[i - 1] == 1 && c == 0) break;
        else fib.push_back(c);
        i++;
    }
    for (auto i : fib) {
        std::cout << fib[i] << " ";
    }

    return 1;

}


int main() {
    int n;
    std::cin >> n;
    get_fibonacci_last_digit_fast(n);
    //  std::cout << c << '\n';
}
