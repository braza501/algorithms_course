#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::vector;
enum Type {
    START, POINT, END
};

bool comparator(const std::pair<int, std::pair<Type, int>> &a, const std::pair<int, std::pair<Type, int>> &b) {
    if (a.first < b.first) return true;
    if (a.first > b.first) return false;

    return (int) a.second.first < (int) b.second.first;
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> cnt(points.size());
    //std::vector<std::string> str = {"START","POINT", "END"};
    std::vector<std::pair<int, std::pair<Type, int>>> elements;
//    std::unordered_map<int, int> indices;
    for (int i = 0; i < points.size(); i++) {
        elements.push_back(std::make_pair(points[i], std::make_pair(POINT, i)));
//        indices[points[i]] = i;
    }
    for (auto &&x:ends) {
        elements.push_back(std::make_pair(x, std::make_pair(END, 0)));
    }
    for (auto &&x:starts) {
        elements.push_back(std::make_pair(x, std::make_pair(START, 0)));
    }
    std::sort(elements.begin(), elements.end(), comparator);
    int count = 0;
//    for (auto &&x: elements) {
//        std::cout<<x.first << " " <<str[x.second] <<" ";
//    }
    for (auto &&x: elements) {
        if (x.second.first == Type::START) {
            count++;
        } else if (x.second.first == Type::END) {
            count--;
        } else {
            cnt[x.second.second] = count;
        }
    }

    return cnt;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<int> starts(n), ends(n);
    for (size_t i = 0; i < starts.size(); i++) {
        std::cin >> starts[i] >> ends[i];
    }
    vector<int> points(m);
    for (size_t i = 0; i < points.size(); i++) {
        std::cin >> points[i];
    }

    vector<int> cnt = fast_count_segments(starts, ends, points);
    for (size_t i = 0; i < cnt.size(); i++) {
        std::cout << cnt[i] << ' ';
    }
}
