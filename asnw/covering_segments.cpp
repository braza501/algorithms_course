#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <deque>

using std::vector;

struct Segment {
    int start, end;
};

bool comp(const Segment &a, const Segment &b) {
    return a.end < b.end;
}

bool is_contained(const Segment &segment, int point) {
    return (segment.start <= point && point <= segment.end);
}

vector<int> optimal_points(vector<Segment> &segments) {
    vector<int> points;
    std::sort(segments.begin(), segments.end(), comp);
    std::deque<Segment> aux(segments.cbegin(), segments.cend());


    while (!aux.empty()) {
        int point = aux.front().end;
        aux.pop_front();
        points.push_back(point);
        for (auto it = aux.begin(); it != aux.end();) {
            if (is_contained(*it, point)) {
                it = aux.erase(it);
            } else {
                ++it;
            }
        }
    }

    return points;
}

int main() {
    int n;
    std::cin >> n;
    vector<Segment> segments(n);
    for (size_t i = 0; i < segments.size(); ++i) {
        std::cin >> segments[i].start >> segments[i].end;
    }
    vector<int> points = optimal_points(segments);
    std::cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << points[i] << " ";
    }
}
