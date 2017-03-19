#include <iostream>
#include <vector>
#include <algorithm>
#include <sys/resource.h>

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
    int n;
    vector<int> key;
    vector<int> left;
    vector<int> right;

public:
    void read() {
        cin >> n;
        key.resize(n);
        left.resize(n);
        right.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> key[i] >> left[i] >> right[i];
        }
    }

    void in_order(int node, vector<int> &result) {
        if (left[node] != -1) {
            in_order(left[node], result);
        }
        result.push_back(key[node]);
        if (right[node] != -1) {
            in_order(right[node], result);
        }
    }


    vector<int> in_order() {
        vector<int> result;
        in_order(0, result);
        return result;
    }

    void pre_order(int node, vector<int> &result) {

        result.push_back(key[node]);
        if (left[node] != -1) {
            pre_order(left[node], result);
        }
        if (right[node] != -1) {
            pre_order(right[node], result);
        }
    }

    vector<int> pre_order() {
        vector<int> result;
        pre_order(0, result);
        return result;
    }

    void post_order(int node, vector<int> &result) {

        if (left[node] != -1) {
            post_order(left[node], result);
        }
        if (right[node] != -1) {
            post_order(right[node], result);
        }
        result.push_back(key[node]);
    }

    vector<int> post_order() {
        vector<int> result;
        post_order(0, result);
        return result;
    }
};

void print(vector<int> a) {
    for (size_t i = 0; i < a.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
}

int main_with_large_stack_space() {
    ios_base::sync_with_stdio(0);
    TreeOrders t;
    t.read();
    print(t.in_order());
    print(t.pre_order());
    print(t.post_order());
    return 0;
}

int main(int argc, char **argv) {
    // Allow larger stack space
    const rlim_t kStackSize = 128 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0) {
        if (rl.rlim_cur < kStackSize) {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0) {
                std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }

    return main_with_large_stack_space();
}

