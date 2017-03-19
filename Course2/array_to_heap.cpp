#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
private:
    vector<int> data_;
    vector<pair<int, int> > swaps_;

    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> data_[i];
    }

    void sift_down(int k) {
        int n = data_.size();
        while (2 * k + 1 < n) {
            int j = 2 * k + 1;
            if (j < n - 1 && data_[j] > data_[j + 1]) j++;
            if (data_[k] <= data_[j]) break;
            std::swap(data_[k], data_[j]);
            swaps_.push_back(make_pair(k, j));
            k = j;
        }
    }

    void GenerateSwaps() {
        swaps_.clear();
        int n = data_.size();
        for (int k = (n - 1) / 2; k >= 0; k--)
            sift_down(k);
    }

public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
