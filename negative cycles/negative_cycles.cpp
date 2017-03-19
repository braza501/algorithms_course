#include <iostream>
#include <vector>

using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost, int source) {
    vector<int> dist(adj.size(), INT32_MAX);
    dist[source] = 0;

    for (int i = 0; i < adj.size() - 1; i++) {
        bool flag = false;
        for (int v = 0; v < adj.size(); v++) {
            int j = 0;
            for (int w : adj[v]) {
                if (dist[w] > dist[v] + cost[v][j] && dist[v] != INT32_MAX) {
                    dist[w] = dist[v] + cost[v][j];
                    flag = true;
                }
                j++;
            }
        }
        if (!flag) return 0;
    }

    for (int v = 0; v < adj.size(); v++) {
        int j = 0;
        for (int w : adj[v]) {
            if (dist[w] > dist[v] + cost[v][j] && dist[v] != INT32_MAX) {
                return 1;
            }
            j++;
        }
    }


    return 0;
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

    for (int i = 0; i < adj.size(); i++) {
        if (negative_cycle(adj, cost, i) == 1) {
            std::cout << 1 << std::endl;
            return 0;
        }
    }
    std::cout << 0 << std::endl;
}
