#include <iostream>
#include <vector>

using std::vector;
using std::pair;
long long count = 0;

void dfs(int v, vector<bool> &marked, const vector<vector<int>> &adj) {
    marked[v] = true;

    for (int w : adj[v]) {
        if (!marked[w]) {
            dfs(w, marked, adj);
        }
    }
}

int reach(vector<vector<int>> &adj) {
    vector<bool> marked(adj.size());

    for (int i = 0; i < adj.size(); i++) {
        if (!marked[i]) {
            dfs(i, marked, adj);
            count++;
        }
    }

    return count;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    std::cout << reach(adj);
}
