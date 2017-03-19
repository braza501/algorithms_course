#include <iostream>

long gcd_fast(long a, long b) {
    if (b == 0) {
        return a;
    }
    return gcd_fast(b, a % b);
}

long long lcm_fast(long a, long b) {
    return a / gcd_fast(a, b) * b;
}

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << lcm_fast(a, b) << std::endl;
    return 0;
}
