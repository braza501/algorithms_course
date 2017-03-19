#include <iostream>
#include <vector>

using std::vector;
using std::pair;

int reach(vector<vector<int>> &adj, int x, int y) {
    vector<int>distTo(adj.size());
    vector<bool> marked(adj.size());
    std::queue<int> q;

    for (int v = 0; v < adj.size(); v++)
        distTo[v] = -1;

    distTo[x] = 0;
    marked[x] = true;
    q.enqueue(s);

    while (!q.isEmpty()) {
        int v = q.front();
        q.pop();
        for (int w : adj[v]) {
            if (!marked[w]) {
                distTo[w] = distTo[v] + 1;
                marked[w] = true;
                q.push(w);
            }
        }
    }


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
    int x, y;
    std::cin >> x >> y;
    std::cout << reach(adj, x - 1, y - 1);
}
