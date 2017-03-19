#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>

using std::vector;
struct Point {
    int id;
    int x;
    int y;
};

struct Edge {
    long double weight;
    int id_one;
    int id_two;

    bool operator<(const Edge &other) const {
        return weight > other.weight;
    }
};

long double distance(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct DisjointSetsElement {
    int parent, rank;

    DisjointSetsElement( int parent = -1, int rank = 0) :
            parent(parent), rank(rank) {}
};

struct DisjointSets {
    int size;
    vector<DisjointSetsElement> sets;

    DisjointSets(int size) : size(size), sets(size) {
        for (int i = 0; i < size; i++)
            sets[i].parent = i;
    }

    int getParent(int id) {
        while (id != sets[id].parent) {
            sets[id] = sets[sets[id].parent].parent;
            id = sets[id].parent;
        }
        return id;
    }

    void merge(int destination, int source) {
        int realDestination = getParent(destination);
        int realSource = getParent(source);
        if (realDestination != realSource) {
            if (sets[realDestination].rank < sets[realSource].rank) {
                sets[realDestination].parent = realSource;
            } else if (sets[realDestination].rank > sets[realSource].rank) {
                sets[realSource].parent = realDestination;

            } else {
                sets[realSource].parent = realDestination;
                sets[realDestination].rank++;
            }

        }
    }
};

int main() {

    size_t n;
    std::cin >> n;
    vector<Point> points;
    std::priority_queue<Edge> edges;
    DisjointSets uf(n);
    for (size_t i = 0; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        Point point;
        point.id = i;
        point.x = x;
        point.y = y;
        points.push_back(point);
    }
    for (size_t i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long double weight = distance(points[i], points[j]);
            Edge edge;
            edge.weight = weight;
            edge.id_one = points[i].id;
            edge.id_two = points[j].id;
            edges.push(edge);
        }
    }

    vector<Edge> mst;
    double result = 0.0;
    while (!edges.empty() && mst.size() < n - 1) {
        Edge e = edges.top();
        edges.pop();
        int v = e.id_two;
        int w = e.id_one;
        if (!(uf.getParent(v) == uf.getParent(w))) {
            uf.merge(v, w);
            mst.push_back(e);
            result += e.weight;
        }
    }

    std::cout << std::setprecision(10) << result << std::endl;
}
