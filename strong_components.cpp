#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using std::vector;
using std::pair;

int count = 0;

void dfs(int v, vector<bool> &marked, const vector<vector<int>> &adj, std::stack<int> &order) {
    marked[v] = true;

    for (int w : adj[v]) {
        if (!marked[w]) {
            dfs(w, marked, adj, order);
        }
    }
    order.push(v);
}

std::stack<int> toposort(const vector<vector<int> >& adj) {
    vector<bool> marked(adj.size());
    std::stack<int> order;
    for (int i = 0; i < adj.size(); i++) {
        if (!marked[i]) {
            dfs(i, marked, adj, order);
        }
    }
    return order;
}

int number_of_strongly_connected_components(vector<vector<int> > adj) {
    vector<vector<int> > reverse(adj.size());
    for (int u = 0; u < reverse.size(); u++) {
        for (int v : adj[u]) {
            reverse[v].push_back(u);
        }
    }
    std::stack<int> order = toposort(reverse);
    std::stack<int> empty;
    vector<bool> marked(adj.size());
    while (!order.empty()) {
        if (!marked[order.top()]) {
            dfs(order.top(), marked, adj, empty);
            count++;
        }
        order.pop();
    }
    return count;
}
int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    std::cout << number_of_strongly_connected_components(adj);
}
