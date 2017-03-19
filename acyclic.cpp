#include <iostream>
#include <vector>

using std::vector;
using std::pair;
vector<bool> on_current_path;
bool cycle = false;

void dfs(int v, vector<bool> &marked, const vector<vector<int>> &adj) {
    marked[v] = true;
    on_current_path[v] = true;
    for (int w : adj[v]) {
        if (cycle) return;

        if (!marked[w]) {
            dfs(w, marked, adj);
        } else if (on_current_path[w]) {
            cycle = true;
        }
    }
    on_current_path[v] = false;
}

int acyclic(vector<vector<int> > &adj) {

    vector<bool> marked(adj.size());

    for (int i = 0; i < adj.size(); i++) {
        if (!marked[i] && cycle == false) {
            dfs(i, marked, adj);
        }
    }
    return cycle ? 1 : 0;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    on_current_path.resize(n);
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    std::cout << acyclic(adj);
}
