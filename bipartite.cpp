#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

vector<bool> color;
bool bipartite = true;

void dfs(int v, vector<bool> &marked, const vector<vector<int>> &adj) {
    marked[v] = true;

    for (int w : adj[v]) {
        if (!bipartite) return;

        if (!marked[w]) {
            color[w] = !color[v];
            dfs(w, marked, adj);
        } else if (color[w] == color[v]) {
            bipartite = false;
        }
    }
}

int bipart(vector<vector<int> > &adj) {
    color.resize(adj.size());
    bipartite = true;
    vector<bool> marked(adj.size());

    for (int v = 0; v < adj.size(); v++) {
        if (!marked[v]) {
            dfs(v,marked,adj);
        }
    }
    return bipartite ? 1 : 0;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    std::cout << bipart(adj);
}
