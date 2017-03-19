#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

struct Vertex {
    int value;
    int distance;

    bool operator<(const Vertex &other) const {
        return distance > other.distance;
    }
};

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
    vector<bool> used(adj.size());
    priority_queue<Vertex> queue;
    vector<int> dist(adj.size(), INT32_MAX);
    dist[s] = 0;

    for (int i = 0; i < adj.size(); i++) {
        Vertex vertex;
        vertex.distance = dist[i];
        vertex.value = i;
        queue.push(vertex);
    }
    while (!queue.empty()) {
        Vertex u = queue.top();
        queue.pop();
        if (used[u.value]) {
            continue;
        }
        used[u.value] = true;
        int j = 0;
        for (int w : adj[u.value]) {
            if (dist[w] > dist[u.value] + cost[u.value][j] && dist[u.value] != INT32_MAX) {
                dist[w] = dist[u.value] + cost[u.value][j];
                Vertex to_add;
                to_add.distance = dist[w];
                to_add.value = w;
                queue.push(to_add);
            }
            j++;
        }
    }
    return dist[t] == INT32_MAX ? -1 : dist[t];
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, cost, s, t);
}
