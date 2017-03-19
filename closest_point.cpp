#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <climits>


using std::vector;
using std::string;
using std::pair;
using std::min;

struct Point {
    long long x, y;

    Point(long long x_, long long y_) : x(x_), y(y_) {}
};


bool comparator_x(const Point &a, const Point &b) {
    return a.x < b.x;
}

bool comparator_y(const Point &a, const Point &b) {
    return a.y < b.y;
}

long double distance(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

long double brute_force(vector<Point> &points, size_t left, size_t right) {
    long double min = std::numeric_limits<long double>::max();
    for (int i = left; i <= right; ++i)
        for (int j = i + 1; j <= right; ++j)
            if (distance(points[i], points[j]) < min)
                min = distance(points[i], points[j]);
    return min;
}

long double check_boundary(vector<Point> &a, long double min_dist) {
    long double min = min_dist;
    std::sort(a.begin(), a.end(), comparator_y);

    for (int i = 0; i < a.size(); ++i)
        for (int j = i + 1; j < a.size() && (a[j].y - a[i].y) < min; ++j)
            if (distance(a[i], a[j]) < min)
                min = distance(a[i], a[j]);

    return min;
}

long double min_distance(vector<Point> &a, size_t left, size_t right) {
    if (right - left <= 7) return brute_force(a, left, right);

    size_t mid = left + (right - left) / 2;
    long double one = min_distance(a, left, mid);
    long double two = min_distance(a, mid + 1, right);

    long double min_dist = std::min(one, two);

    vector<Point> delta_array;
    for (int i = left; i <= right; i++)
        if (abs(a[i].x - a[mid].x) < min_dist)
            delta_array.push_back(a[i]);

    return std::min(min_dist, check_boundary(delta_array, min_dist));
}

long double minimal_distance(vector<long long> &x, vector<long long> &y) {
    std::vector<Point> a;
    for (int i = 0; i < x.size(); i++) {
        a.push_back(Point(x[i], y[i]));
    }
    std::sort(a.begin(), a.end(), comparator_x);
    return min_distance(a, 0, a.size() - 1);
}

bool is_ok(long double a, long double b) {
    return (fabs(a - b) <= 0.001 || a == b );
}

//int main() {
//    srand(time(NULL));
//    while (true) {
//        size_t n;
//
//        n = 2 + std::rand() % (100000 - 1);
//        vector<int> x(n);
//        vector<int> y(n);
//        for (size_t i = 0; i < n; i++) {
//            x[i] = std::rand() % 1000000;
//            y[i] = std::rand() % 1000000;
//        }
//        std::vector<Point> a;
//        for (int i = 0; i < x.size(); i++) {
//            a.push_back(Point(x[i], y[i]));
//        }
//
//        long double one = minimal_distance(x, y);
//        long double two = brute_force(a, 0, a.size() - 1);
//        if (is_ok(one, two)) {
//            std::cout << one << " " << two << std::endl;
//            std::cout << "OK!";
//
//        }else {
//            std::cout << one << " " << two << std::endl;
//            std::cout << fabs(one - two) << std::endl;
//            std::cout << "FAIL!" << std::endl;
//            for (auto &&var: a) {
//                std::cout << var.x << " " << var.y << std::endl;
//            }
//            return EXIT_FAILURE;
//        }
//    }
//}

int main() {
    size_t n;
    std::cin >> n;
    vector<long long> x(n);
    vector<long long> y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    std::cout << std::fixed;
    std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";
}

